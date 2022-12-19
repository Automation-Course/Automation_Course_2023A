//libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define servoPin 11
//set the LCD address for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,16,2);
Servo servo_11;
 
// pin Variables
const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
int push = 0;
bool openGate = false;
int speed = 90;
 
long duration,cm;
 
 
void setup()
{
  Serial.begin(9600); // Starting Serial Terminal
  lcd.init(); //initialize lcd screen
  lcd.backlight(); // turn on the backlight
  servo_11.attach(11);
 
   pinMode (11,INPUT);
   pinMode (10,INPUT);
   pinMode (4, INPUT);
}
 
 
//~ Looping ~
 
void loop()
{
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
     
  cm = microsecondsToCm(duration);
  printCmDistance(cm);
 
  if ( cm > 20)
  {
    lcdScreen1();
    digitalWrite(10,HIGH); //red ON
    digitalWrite(9,LOW);  //green OFF
  }
  else
  {
    lcdScreen2();
    digitalWrite(10,LOW); //red OFF
    digitalWrite(9,HIGH); //green ON
  }
  push = digitalRead(4);
  if ((push == 1)&&(ultraSonic()<=20))
    openGate = true;
  if ((openGate)&&(speed=90)) //not move right now
  {
    servo_11.write(80); //open
    delay(1000);
    servo_11.write(100); //close
    openGate = false;
    delay(1300);
    speed = 90;
  }
  else
  {
    servo_11.write(90);
    openGate = false;
    push=0;
  }
}
 
  long microsecondsToCm(long microseconds)
    {
      return microseconds / 29 / 2;
    }
 
 
  // printDistance
  void printCmDistance(long cm)
    {
      Serial.print(cm);
      Serial.print("cm");
      Serial.println();
    }
 
      // Define and run LCD screen 1
  void lcdScreen1()
    {
      lcd.setCursor(4,0);
      lcd.print("WELCOME     ");
      //delay(500); //0.5 sec
      lcd.setCursor(2,1);
      lcd.print("Group 7 ROCKS");
    }
 
  // Define and run LCD screen 2
  void lcdScreen2()
    {
      lcd.setCursor(4,0);
      lcd.print("Please Press");
      lcd.setCursor(2,1);
      lcd.print("  the  button");
    }
 
  long ultraSonic()
    {
      long duration,cm;
      pinMode(pingPin, OUTPUT);
      digitalWrite(pingPin, LOW);
      delayMicroseconds(2);
      digitalWrite(pingPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(pingPin, LOW);
      pinMode(echoPin, INPUT);
      duration = pulseIn(echoPin, HIGH);
      cm = microsecondsToCm(duration);
      return cm;
    }
