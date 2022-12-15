#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h> 
#define servoPin 9
#define ledPin 13
#define ButtonPin 2
Servo servo;
int trigPin = 10;
int echoPin = 5;
int sensorActivationRange = 20;
int angle;
double distance;
double duration;
byte lastButtonState;
byte currentButtonState;
byte ledState = LOW;
bool systemIsON = false;
long previousMillisDis = 0;
long currentMillisDis = 0;
long previousMillisLed = 0;
long currentMillisLed = 0;
int intervalDis = 1000;
int intervalLed = 5000;
LiquidCrystal_I2C lcd_Screen(0x27, 16, 2);
 
void setup() 
{
 servo.attach(servoPin);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);  
 lcd_Screen.init();
 pinMode(ButtonPin, INPUT);
 pinMode(ledPin, OUTPUT);
 lastButtonState = digitalRead(ButtonPin);
 Serial.begin(9600);
  
}
 
void loop() {
  currentButtonState = digitalRead(ButtonPin); //get the butten state
  buttonFunction();
  ultrasonicSensor();
  if(systemIsON == true){ // if the system is on
    if(distance <= sensorActivationRange){ // if the distance from the sensor measuring is less then the range we defined
      servo.attach(servoPin);
      lcd_Screen.setCursor(0,0);
      lcd_Screen.print("Intruder alert!"); // print message to the lcd screen
      startWorking(); // activate the servo 
    }
    else{
      lcd_Screen.clear(); 
      servo.detach();  //stop the servo 
    }
  }

  SerialMonitorPrints(); // print the ultrasonic measurment distance every 1 second, and the system state every 5 seconds

}

void SerialMonitorPrints(){// print the ultrasonic measurment distance every 1 second, and the system state every 5 seconds
  currentMillisDis = millis();
  currentMillisLed = millis();
  if (currentMillisDis - previousMillisDis >= intervalDis == true ) { 
    Serial.print("The distance is: ");
    Serial.println(distance);
    previousMillisDis = currentMillisDis;
  }
    if (currentMillisLed - previousMillisLed >= intervalLed == true ) {
    Serial.print("The system state is: ");
    Serial.println(ledState);
    previousMillisLed = currentMillisLed;
  }
}


 
void ultrasonicSensor(){ // the ultrasonic sensor measurement function
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // get the duration from the sensor
  distance = duration*0.034/2; // calc the distance using the duration we get from the sensor
}

void buttonFunction(){ // changing the system state according to the button state
  
  if (currentButtonState != lastButtonState){ //if the butten state was change
    lastButtonState = currentButtonState; // make the new state be the current state
    if (currentButtonState == LOW){ // if the state of the butten changed to LOW by pressing it
      if(ledState == HIGH){ // if the led is working, the system is ON and we want to turn off the system
        ledState = LOW; // change the state to low
        digitalWrite(ledPin, ledState);// turn off the led
        lcd_Screen.clear(); //clear the lcd screen
        lcd_Screen.setCursor(1,0); // locate the lcd text
   	  	lcd_Screen.print("System is OFF"); //print to the lcd screen
        delay(3000); // wait 3 secounts
        lcd_Screen.clear(); // clear the screen aften waiting 3 seconds
        lcd_Screen.noBacklight(); // turn off the lcd screen lights
        systemIsON = false; // change the system status in to off
        servo.detach(); // stop the servo
      }
      else { // if the led is on low, the system is OFF
        ledState = HIGH; // change the led state to high
        digitalWrite(ledPin, ledState);// turn ON the led 
        systemIsON = true; // change the system status in to ON
        servo.attach(servoPin);// attach the servo
        lcd_Screen.setCursor(1,0);// locate the lcd text
        lcd_Screen.backlight();// turn on the lcd lights
   	  	lcd_Screen.print("System is ON!");//print to the lcd screen
        delay(3000);// wait 3 secounts
        lcd_Screen.clear();// clear the screen aften waiting 3 seconds
      }
    }
  } 
}

void startWorking(){ //CHANGING THE SERVO ANGLES
  if (angle <= 180){ // if the angle of the servo is less then 180
  servo.write(angle);
  angle ++; // add 1 to the angle
  }else{// if the angle is more then 180 
  servo.write(angle);
  angle --;// reduse 1 from angle
  }
}

  
