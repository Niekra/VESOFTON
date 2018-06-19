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

int currentUser = 0;

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
user_t user5;

//user_t users[5];
user_t users[5]; //remove after first time.


//backup



/************ Program variables **************************/
char input_buffer[BUFFER_SIZE] = {0};
int buffer_index = 0;

char input1;
char split_buffer[5];
char input2;
int input3;

/************ modus variables **************************/
int modus_timer = 0;
int modus_state = 0;
int max_state = 0;

/************ vibration variables **************************/
volatile long timer0_counter = 0;

/************ vibration variables **************************/


void setup(){
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.println("master");
  //remove after first use.
  char c = EEPROM.read(500);
  Serial.println(c);
  if(c != '3')
  {
    EEPROM.write(500, '3');
    //EEPROM_writeAnything(0, users);
    EEPROM.put(0,user1);
    EEPROM.put(75,user2);
    EEPROM.put(150,user3);
    EEPROM.put(225,user4);
    EEPROM.put(300,user5);
    Serial.println(user1.eye_off_duration);
    delay(100);
  }
  EEPROM.get(0, user1);
  EEPROM.get(75, user2);
  EEPROM.get(150, user3);
  EEPROM.get(225, user4);
  EEPROM.get(300, user5);
  delay(100);
  Serial.println(user1.eye_off_duration);
  //EEPROM_readAnything(0, users);
  users[0] = user1;
  users[1] = user2;
  users[2] = user3;
  users[3] = user4;
  users[4] = user5;
  
  //users = [user1,user2,user3,user4,user5];

  delay(100);
  Serial.println(users[currentUser].eye_off_duration);

/************ GPIO **************************/
  pinMode(TRIL_MOTOR1, OUTPUT);
  digitalWrite(TRIL_MOTOR1, LOW);
  pinMode(TRIL_MOTOR2, OUTPUT);
  digitalWrite(TRIL_MOTOR2, LOW);
  pinMode(AMPPIN, OUTPUT);
  digitalWrite(AMPPIN, LOW);

  //TODO load user data and start first 

  mp3.begin(9600);
  delay(500);

  sendCommand(CMD_SEL_DEV, DEV_TF);
  delay(500);

  BTserial.begin(9600);
  delay(500);

  mTimer();

  setupUser();
  //sendMP3Command(p);

  //sendCommand(CMD_PLAY_W_VOL, 0X1903);//play the first song with volume 15 class
  
}

void loop(){

  buffer_index = 0;
  delay(100);
  while (Serial.available())
  {
    input_buffer[buffer_index] = Serial.read();
    buffer_index++;
  }

  if(input_buffer[buffer_index-1] == '!'){
    input_buffer[buffer_index-1] = '\0';
    Serial.println(input_buffer);

    input1 = input_buffer[0];
    Serial.println(input1);
    input2 = input_buffer[1];
    Serial.println(input2);
    for(int i = 2; i<buffer_index; i++)
    {
      if(input_buffer[i] != ',' && input_buffer[i] != '\0')
      {
        split_buffer[i-2] = input_buffer[i];
      }else
      {
        input3 = atoi(split_buffer);
        Serial.println(input3);
      }
    }
    clear_buffer();
    clear_split_buffer();

    if(!input3){
      input3 = 0;
    }  
  
    switch(input1)
      {
      case 's':
        //TODO: additional music functions
        sendMP3Command(input2, input3);
        break;
      case 'v':   
        vib_manager(input2, input3);
        break;
      case 'l':
        light_manager(input2, input3);
        break;
      case 'u':
        //TODO: gebruiker functions
        user_manager(input2, input3);
        break;
      case 'm':
        //TODO: meer modus functions
        modus_manager(input2, input3);
        break;
      }
  }
  input3 = 0;
  delay(100);
  check_modus();
  
}

void clear_buffer()
{
  for(int i = 0; i<BUFFER_SIZE; i++)
  {
    input_buffer[i] = ' ';
  }
}

void clear_split_buffer()
{
  for(int i = 0; i<5; i++)
  {
    split_buffer[i] = '\0';
  }
}




