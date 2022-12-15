//#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>

#include <LiquidCrystal_I2C.h>

#include <Wire.h> 
//#include<hd44780.h>
//#include <hd44780ioClass/hd44780_I2Cexp.h>
//hd44780_I2Cexp lcd;
Servo servo;
int pushButtonPin=2; 
int greenLedPin=10; // connect Green LED to pin 10 (PWM pin)
int redLedPin=11; // connect Red LED to pin 11 (PWM pin)
int servoPin=9;
int triggerPin=7;
int echoPin=8;
int maxRange = 300; // Maximum range  
int minRange = 0; // Minimum range  
long centim=0;//ultra Sonic
int duration=0;//ultra Sonic
//Adafruit_LiquidCrystal lcd_1(0);

int pushButtonValue;
boolean start = false;
boolean readDistance = false;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
 LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() 
{ 
  
  	pinMode(greenLedPin, OUTPUT);
  	pinMode(redLedPin, OUTPUT);
  	pinMode(servoPin,OUTPUT);
  	pinMode(pushButtonPin,INPUT);
    digitalWrite(pushButtonPin,HIGH);
  	pinMode(triggerPin,INPUT);
 	  pinMode(echoPin,OUTPUT);
  
    Serial.println("set up done");
  //LCD For Simulator:
    lcd.begin(16, 2);
  
//LCD For Real:
    //initialize the LCD
	 lcd.init();
  lcd.backlight();
Serial.begin(9600); 

  
}


void loop()
{
  Serial.println(centim);
  // קריאת ערכים מהחיישנים
  pushButtonValue = digitalRead(pushButtonPin);
  //ultrasonicCheck();
  centim=readUltrasonicDistance(7,8)/58;
  if (pushButtonValue == 0){
  

      if (centim >= 10){
        
        digitalWrite(greenLedPin, HIGH); //הדלקת נורה ירוקה
        digitalWrite(redLedPin,LOW);
        startServo(); //לסובב את מנוע הסרבו
      }
      else {
       
        digitalWrite(redLedPin, HIGH); //הדלקת נורה ירוקה
        digitalWrite(greenLedPin, LOW);
        printToLCD(); //הדפסת הודעה מתאימה למסך
      }
   }
} // end LOOP


// ------------ Functions --------------

void startServo(){ // סיבוב מנוע הסרבו
  servo.attach(servoPin);
  servo.write(300);
}

void redLightBlinking(){
  for(int i=0 ; i < 5 ; i++){
    digitalWrite(redLedPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  	delay(1000);              // wait for a second
    digitalWrite(redLedPin, LOW);    // turn the LED off by making the voltage LOW
  	delay(1000); 
  }
}

void printToLCD(){
  lcd.setBacklight(1);
  lcd.setCursor(0, 0);
  lcd.print("You're too close");
  lcd.setCursor(0, 1);
  lcd.print("to the screen!");
  delay(500); // Wait for 500 millisecond(s)
  lcd.setBacklight(0);
  delay(500); // Wait for 500 millisecond(s)

}



// ------------ Ultrasonic --------------


long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}