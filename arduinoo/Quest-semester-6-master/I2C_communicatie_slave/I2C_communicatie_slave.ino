#include <Wire.h>
#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 30
#define DATA_PIN 6
#define pwm 5
#define FORWARD 0
#define BACKWARD 1
#define SLOW 250
#define MEDIUM 50
#define FAST 5
#define EYE1 5
#define EYE2 3

CRGB leds[NUM_LEDS];
CRGB z = CRGB::Black;

boolean direction = FORWARD;

int strip_on = 0;
int strip_modus = 0;

volatile long eye_counter = 1000;
long eye_on_duration = 1000;
long eye_off_duration = 5000;

int eye_intensity = 255;
int eye_modus = 0;
int eye_status = 0;
int cycles = 10;

int speed =100;

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  Serial.println("slave");

  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  delay(500);
  allColor(z);
  randomSeed(analogRead(0));
  pinMode(EYE1, OUTPUT);
  pinMode(EYE2, OUTPUT);
  pinMode;
  //analogWrite(pwm, 255);
  digitalWrite(EYE1, LOW);
  digitalWrite(EYE2, LOW);
  //rainbow(0,NULL);

  mTimer();
  
}

void loop() {
  if(strip_on == 1)
  {
    switch(strip_modus)
    {
      case 0:
       Serial.print(0);
        allColor(randomColor());
        delay(1000);
        break;
      case 1:
        Serial.print(1);
        allRandom();
        delay(500);
        break;
      case 2:
        Serial.print(2);
        allColor(leds);
        disolve(1, cycles, speed);
        break;
      case 3:
        Serial.print(3);
        flash(randomColor(), 4, speed*10);
        break;
      case 4:
        Serial.print(4);
        colorWipe(randomColor(), speed, FORWARD);
        break;
      case 5:
        Serial.print(5);
        rainbow(1, speed/15);
        break;
      case 6:
        Serial.print(6);
        theaterChase(randomColor(), 1, speed*2);
        break;
      case 7:
        Serial.print(7);
        theaterChaseRainbow(1, speed*2);
        break;
      case 8:
        Serial.print(8);
        lightning(randomColor(), 3, 1, speed/2);
        break;
      case 9:
        Serial.print(9);
        cylon(randomColor(), 3, speed/2);
        break;
      case 10:
        Serial.print(10);
        stripes(randomColor(), randomColor(), 1);
        delay(1000);
        break;                  
    }
  }else{
    delay(100);
  }

  check_eye();
  
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  char input_buffer[6];
  char split_buffer[5];
  char input1;
  int i = 0;
  int input2;

  for(int z = 0; z<5; z++)
  {
    split_buffer[z] = '\0';
  }

  for(int z = 0; z<6; z++)
  {
    input_buffer[z] = '\0';
  }

  while (Wire.available()) { // loop through all but the last
    input_buffer[i] = Wire.read(); // receive byte as a character
    i++;
  }
  input1 = input_buffer[0];
  //Serial.println(input1);         // print the character

  for(int x = 1; x<i; x++)
  {
    split_buffer[x-1] = input_buffer[x];
    //Serial.println(split_buffer[x-1]);
  }

  input2 = atoi(split_buffer);
  //Serial.println(input2);         // print the character
  if(!input2){
      input2 = 0;
  }  
  light_manager(input1, input2);

}

  
 

