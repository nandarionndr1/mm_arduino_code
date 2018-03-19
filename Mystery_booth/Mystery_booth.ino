
// Arduino coin acceptor code by hxlnt
// Originally created for "Adding a Coin Acceptor to Your Arduino Project" on the Maker Show
// See the entire video tutorial at https://channel9.msdn.com/Shows/themakershow/10
// 
// Read your coin acceptor's specs and instructions first for hookup specifics
// Modifications to this code may be needed
// Coin acceptor model used in this example is JY-923
//

#include <stdio.h>

//Download the following libraries listed below.
#include "Keypad.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
using namespace std;

//Constants
const byte ROWS = 4; //number of rows on the keypad i.e. 4
const byte COLUMNS = 3; //number of columns on the keypad i,e, 3
const String PASSCODE = "3473";
const int interruptPin = 2;
const int buzzerPin = 12; //buzzer to arduino pin 9
//Global variables
boolean isAvailable = false;
volatile byte state = LOW;
int ctr = 0;
boolean play = false;
String code = "";

//Keypad
char keymap[ROWS][COLUMNS]={{'1', '2', '3'},
                            {'4', '5', '6'},
                            {'7', '8', '9'},
                            {'*', '0', '#'}
                            };
byte rowPins[ROWS]= {4,9,8,6};
byte columnPins[COLUMNS]= {5,3,7};
Keypad kpd= Keypad(makeKeymap(keymap), rowPins, columnPins, ROWS, COLUMNS);

void setup() {
  Serial.begin(9600);
  
  pinMode(buzzerPin, OUTPUT);
  mySoftwareSerial.begin(9600);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  //myDFPlayer.reset();
  Serial.println(F("DFPlayer Mini online."));
  Serial.println("Hello, Calibrated.");
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
}

void loop() { 
 
  if (isAvailable){  
     char keypressed = kpd.getKey();
    if (keypressed != NO_KEY)
     { 
          if(keypressed == '#' ){

            code = "";
          }
          else if (keypressed == '*'){
            if (code == PASSCODE){
              const int emLockPin = A1;
              pinMode(emLockPin, OUTPUT);
  
              code = "";
              
              myDFPlayer.volume(15);  //Set volume value. From 0 to 30
              myDFPlayer.play(1);
            }
            ctr = 0;
            code = "";
            return;
          }
          else{
            code=code+keypressed;
          }
          
        tone_dial(keypressed);
        Serial.println(code);
        delay(300);
          
     }
  }
}

void blink() {
  if (isAvailable == false){
    isAvailable = true; 
        
      Serial.println("ACTIVATED");
   }
}
void tone_dial(char key){
  switch(key){
    case '1':
    beep(200,100);
    break;
    beep(250,100);
    case '2':
    beep(300,100);
    break;
    case '3':
    beep(350,100);
    break;
    case '4':
    beep(400,100);
    break;
    case '5':
    beep(450,100);
    break;
    case '6':
    beep(500,100);
    break;
    case '7':
    beep(550,100);
    break;
    case '8':
    beep(600,100);
    break;
    case '9':
    beep(650,100);
    break;
    case '0':
    beep(700,100);
    break;
    case '#':
    beep(750,100);
    break;
    case '*':
    beep(800,100);
    break;
  }  
}
void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(buzzerPin, note, duration);
 

  delay(duration);
 
  //Stop tone on buzzerPin
  noTone(buzzerPin);
 
  delay(20);

}

