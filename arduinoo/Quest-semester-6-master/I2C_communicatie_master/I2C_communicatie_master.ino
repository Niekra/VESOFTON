#include <Wire.h>
#include <SoftwareSerial.h>
#include "defines.h"

SoftwareSerial mp3(ARDUINO_TRANSMIT_PIN, ARDUINO_RECEIVE_PIN);

/************ Audio variables **************************/
static int8_t Send_buf[MP3_SEND] = {0}; // Buffer for Send commands.  // BETTER LOCALLY
static uint8_t ansbuf[MP3_ANS] = {0}; // Buffer for the answers.    // BETTER LOCALLY

String mp3Answer;           // Answer from the MP3.

/************ Program variables **************************/
char input_buffer[BUFFER_SIZE] = {0};
int buffer_index = 0;

char input1;
char split_buffer[5];
char input2;
int input3;

/************ modus variables **************************/
int modus_timer;
long modus_duration;
int modus;
int modus_state;
int max_state;

/************ vibration variables **************************/
int vib_status;
int vib_intensity;
volatile long timer0_counter;
long vib_on_duration;
long vib_off_duration;
int vib_modus;

void setup(){
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.println("master");

/************ GPIO **************************/
  pinMode(TRIL_MOTOR1, OUTPUT);
  digitalWrite(TRIL_MOTOR1, LOW);
  pinMode(TRIL_MOTOR2, OUTPUT);
  digitalWrite(TRIL_MOTOR2, LOW);
  
  vib_status = 0;
  vib_intensity = 255;
  timer0_counter = 0;
  vib_on_duration = 1000;
  vib_off_duration = 1000;
  vib_modus = 0;

  modus_timer = 0;
  modus_duration = 10000;
  modus_state = 0;
  max_state = 0;

  modus = 0;

  mp3.begin(9600);
  delay(500);

  sendCommand(CMD_SEL_DEV, DEV_TF);
  delay(500);

  sendCommand(CMD_VOLUME_DOWN, 0);
  sendCommand(CMD_VOLUME_DOWN, 0);

  mTimer();

  //sendMP3Command(p);

  //sendCommand(CMD_PLAY_W_VOL, 0X1903);//play the first song with volume 15 class
  
}

void loop(){

  buffer_index = 0;

  while (Serial.available())
  {
    input_buffer[buffer_index] = Serial.read();
    buffer_index++;
  }
  
  delay(100);

  if(input_buffer[buffer_index-1] == '!'){
    input_buffer[buffer_index-1] = '\0';
    //Serial.println(input_buffer);

    input1 = input_buffer[0];
    //Serial.println(input1);
    input2 = input_buffer[2];
    //Serial.println(input2);
    for(int i = 4; i<buffer_index; i++)
    {
      if(input_buffer[i] != ',' && input_buffer[i] != '\0')
      {
        split_buffer[i-4] = input_buffer[i];
      }else
      {
        input3 = atoi(split_buffer);
        //Serial.println(input3);
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
        Serial.println("l");
        break;
      case 'u':
        //TODO: gebruiker functions
        break;
      case 'm':
        //TODO: meer modus functions
        modus_manager(input2, input3);
        break;
      }
  }
  input3 = 0;
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




