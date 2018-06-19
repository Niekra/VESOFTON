#include <Wire.h>
#include <SoftwareSerial.h>
#include "defines.h"
#include "EEPROM.h"
#include "EEPROMAnything.h"

SoftwareSerial BTserial(10, 11); // RX | TX
SoftwareSerial mp3(ARDUINO_TRANSMIT_PIN, ARDUINO_RECEIVE_PIN);

/************ Audio variables **************************/
static int8_t Send_buf[MP3_SEND] = {0}; // Buffer for Send commands.  // BETTER LOCALLY
static uint8_t ansbuf[MP3_ANS] = {0}; // Buffer for the answers.    // BETTER LOCALLY

String mp3Answer;           // Answer from the MP3.

//Current user
int currentUser = 0;

//Struct with the user information.
typedef struct
{
  int play_folder = 1;   //user-data;
  int start_song = 1;   //user-data
  int volume = 12;
  int s_status = 0;
  int s_modus = 0;
  long modus_duration = 10000;            //user_datax
  int modus = 0;                      //user-datax
  int vib_status = 0;           //user-datax
  int vib_onoff = 0;
  int vib_intensity = 255;            //user_datax
  long vib_on_duration = 2000;         //user_datax
  long vib_off_duration = 1000;       //user-datax
  int vib_modus = 0;              //user-datax
  int lit_status = 0;       //user-data
  int lit_modus = 0;        //user-data
  int eye_status = 0;       //user-data
  long eye_on_duration = 1000;  //user-data
  long eye_off_duration = 3000; //user-data
  int eye_intensity = 255;    //user-data
}user_t;


user_t user1;
user_t user2;
user_t user3;
user_t user4;
//user_t user5;

//user_t users[5];
user_t users[4];

/************ Program variables **************************/
char input_buffer[BUFFER_SIZE] = {0};     //Buffer for app input
int buffer_index = 0;                     //Buffer index.


//Input variables
char input1;
char split_buffer[5];
char input2;
int input3;

/************ modus variables **************************/
long modus_timer = 0;                
int modus_state = 0;
int max_state = 0;

/************ vibration variables **************************/
volatile long timer0_counter = 0;



void setup(){
  Serial.begin(9600); //Begin debug serial.
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.println("master");
  //check whether c is the same as last time.
 
  char c = EEPROM.read(500);
  Serial.println(c);
  if(c != '2')              //change 'x' for new version
  {
    EEPROM.write(500, '2'); //change 'x' for new version
    //write the user data
    EEPROM.put(0,user1);
    EEPROM.put(75,user2);
    EEPROM.put(150,user3);
    EEPROM.put(225,user4);
    //EEPROM.put(300,user5);
    delay(10);
  }

  //Load the userdata on start-up.
  EEPROM.get(0, user1);
  EEPROM.get(75, user2);
  EEPROM.get(150, user3);
  EEPROM.get(225, user4);
  //EEPROM.get(300, user5);
  delay(10);

  //Debug info
  Serial.print("eye off duration: ");
  Serial.println(user1.eye_off_duration);

  //Set the loaded users in an array for easy use.
  users[0] = user1;
  users[1] = user2;
  users[2] = user3;
  users[3] = user4;
  //users[4] = user5;

/************ GPIO **************************/
  pinMode(TRIL_MOTOR1, OUTPUT); 
  digitalWrite(TRIL_MOTOR1, LOW);
  pinMode(TRIL_MOTOR2, OUTPUT);
  digitalWrite(TRIL_MOTOR2, LOW);
  pinMode(AMPPIN, OUTPUT);
  digitalWrite(AMPPIN, LOW);

  
  // Open mp3 UART channel.
  mp3.begin(9600);
  delay(500);

  // Select TF card.
  sendCommand(CMD_SEL_DEV, DEV_TF);
  delay(500);

  // Open bluetooth channel.
  BTserial.begin(9600);
  delay(500);

  //Setup 1ms interrupt for timing.
  mTimer();

  //Set last settings of user 1
  setupUser();  
}

void loop(){

  //Reset the index of the buffer
  buffer_index = 0;
  //Wait some time after each run.
  //delay(100);
  //Check for bluetooth serial data and save it into the inpur_buffer[].
  while (BTserial.available())
  {
    input_buffer[buffer_index] = BTserial.read();     //Read bt serial byte(char).
    Serial.println(input_buffer[buffer_index]);
    buffer_index++;                                   //Increase buffer index.
  }
  //Serial.println(input_buffer[buffer_index-1]);
  delay(100);

  //Check if last input is a '!'. '!' singles the end of an input.
  if(input_buffer[buffer_index-1] == '!'){
    input_buffer[buffer_index-1] = '\0';      //replace ! with carriage return.
    Serial.print("input: ");
    Serial.println(input_buffer);             //debug info

    input1 = input_buffer[0];   //First input is command type
    input2 = input_buffer[1];   //Second input is the type function
    for(int i = 2; i<buffer_index; i++)
    {
      if(input_buffer[i] != ',' && input_buffer[i] != '\0')
      {
        split_buffer[i-2] = input_buffer[i];
      }else
      {
        input3 = atoi(split_buffer);  // Third input is optional int value.
      }
    }
    
    clear_buffer();         //reset input_buffer
    clear_split_buffer();   //reset split_buffer

    if(!input3){
      input3 = 0;       //Set input3 if none is given.
    }  

    //Switch the input between the differnt types.
    switch(input1)
      {
      case 's':     //Sound
        sendMP3Command(input2, input3);   //Send sound command.
        break;
      case 'v':   //Vibration
        vib_manager(input2, input3);     //Send vibration command.
        break;
      case 'l':   //Light
        light_manager(input2, input3);
        break;
      case 'u':   //User
        Serial.println("Uermanager");
        user_manager(input2, input3);
        break;
      case 'm':   //Mode
        modus_manager(input2, input3);
        break;
      }
    //DEBUG info
    Serial.print("Input 1: ");
    Serial.println(input1);
  }
  
  input3 = 0;   //Reset input 3;
  check_modus(); //Check the the mode functionality. Switching between mode_states.
  
}

//Clear the input_buffer
void clear_buffer()
{
  for(int i = 0; i<BUFFER_SIZE; i++)
  {
    input_buffer[i] = ' ';
  }
}

//Clear the split_buffer
void clear_split_buffer()
{
  for(int i = 0; i<5; i++)
  {
    split_buffer[i] = '\0';
  }
}




