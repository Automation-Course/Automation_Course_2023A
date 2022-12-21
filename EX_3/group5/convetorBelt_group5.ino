#include "LiquidCrystal_I2C.h"
#include <Servo.h>

#define LdrPin A0  // the cell and 10K pulldown are connected to a0
#define servoPin 9
#define LOW_BOUNDARY 110
#define HIGH_BOUNDARY 150

Servo servo;
LiquidCrystal_I2C lcd_1(0x27, 16, 2);

// PHOTO RESISTORS ITMES
int LdrValue = 0;  // the analog reading from the sensor divider
int LedBrightness=0;
// BUTTONS
int buttonPin1 = 2;
int buttonStatus1 = 0;
// LEDS
int ledPin1 = 11;
int ledPin2 = 12;
int ledPin3 = 13;
// CONVEYOR'S CAPABILITIES
bool isStart = 0;
int angle = 0;
bool shouldCont = true;
int checkWarning = 0;
int counter = 0;
bool wasUnder = false;
bool Direction = true; 

void setup(void) {
  /// innit lcd display
  lcd_1.init(); 
  lcd_1.backlight();
  // buttons
  pinMode(buttonPin1, INPUT);
  // photoresistor
  pinMode(LdrPin, INPUT);
  // led (red, green, yellow)
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  Serial.begin(9600);
  servo.attach(servoPin);
}
void loop(void) {
  
  buttonStatus1 = digitalRead(buttonPin1);

  if (buttonStatus1 == 1) {  // start the conveyor
    lcdDisplay("Conveyor belt ON");
    analogWrite(ledPin3, 225);
    newFactory(); // start a new conveyor process
  }
  if (shouldCont && isStart) {
    LdrValue = analogRead(A0);
    // prints for calibration 
    Serial.print("LDR is reading");
    Serial.println("this value->");
	  Serial.println(LdrValue);
    Serial.println("counter value is:");
    Serial.println(counter);
   

    // if light is absorbed by the resistor
    //the conveyor did full rotation
    if (LdrValue < LOW_BOUNDARY) {
      wasUnder = true;
    }
    else if(wasUnder && LdrValue > HIGH_BOUNDARY){
      counter += 1;  // count rotations
      wasUnder = false;
    }
    switch (counter) {
      case 4:                 // first warning
        if (!checkWarning) {  // remove duplication on desplay
          analogWrite(ledPin1, 225);
          checkWarning = 1;
          lcdDisplay("Items passed");
        }
        break;
      case 8:  //second warning and shutdown
        analogWrite(ledPin2, 225);
        analogWrite(ledPin1, 0);
        analogWrite(ledPin3, 0);
        servo.detach();
        shouldCont = false;
        isStart = 0;
        lcdDisplay("Replace pallet");
        break;
    }
    moveServo();
  }
}
// display on lcd different strings
void lcdDisplay(String s) {
  lcd_1.clear();
  lcd_1.print(s);
}
// rotate servo
void moveServo() {
  if (Direction){ 
   angle +=1;
  }else{
   angle -=1; 
  }
  servo.write(angle);
  if(angle == 180)Direction = false; 
  if(angle == 0)Direction = true;
}
// changed pallet for new factory
void newFactory() {
  // reset leds
  analogWrite(ledPin1, 0);
  analogWrite(ledPin2, 0);
  // start again if statement
  isStart = 1;
  shouldCont = true;

  checkWarning = 0;
  angle = 0;
  counter = 0;
  Direction = true;
  servo.attach(servoPin);
}
