#include <LiquidCrystal_I2C.h>
#include <Servo.h>
Servo servo;
#include <Wire.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd_1(0x27, 16, 2);
#define pingPin 4
#define trigPin 5
#define redLed  8
#define greenLed  7
#define PiezoPin  2
  

//Input 
int no_candy_time_duration = 10; // define no candy time duration
int candy_time_duration = 4; // define candy time duration

//Help variables
unsigned long previousMillis=0;
bool isCandyTime = false;
long duration, cm, distance;
int interval;
int interval2;

void setup() {
  interval = 1000*no_candy_time_duration;
  interval2 = 1000*candy_time_duration;
  Serial.begin(9600);
  servo.attach(6);
  lcd_1.init();
  lcd_1.backlight();
  pinMode(pingPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(PiezoPin, OUTPUT);
  digitalWrite(PiezoPin, HIGH);
  
}

void loop() {
  unsigned long currentMillis = millis();
  Serial.println(isCandyTime);
  if((unsigned long)(currentMillis - previousMillis) < interval && isCandyTime == false){
    digitalWrite(redLed, HIGH);
    distance = checkDistance();
    if(distance <= 30){
      printScreen("Dont Touch!! ");
      digitalWrite(PiezoPin, LOW);
      startServo();
    }
    else{
     servo.write(90);
     digitalWrite(PiezoPin, HIGH);
     printScreen("No Candy Time!");
    }
  }
  
  else if ((unsigned long)(currentMillis - previousMillis) >= interval && isCandyTime == false) {
      candyTime();
   }
  
  else if((unsigned long)(currentMillis - previousMillis) >= (interval+interval2) && isCandyTime == true) {
    digitalWrite(greenLed, LOW);
    previousMillis = currentMillis;
    isCandyTime = false;
    printScreen("No Candy Time!");
  }
  
}
void candyTime(){
    servo.write(90);
    digitalWrite(PiezoPin, HIGH);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
  	isCandyTime = true;
    printScreen("Candy Time!   ");
}

void printScreen(String print){
  lcd_1.setCursor(0, 0);
  lcd_1.print(print);
}

double checkDistance(){

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the pingPin, returns the sound wave travel time in microseconds
  duration = pulseIn(pingPin, HIGH);
  // convert the time into a distance
  // Calculating the distance
  distance = duration * 0.034 / 2; 
  // Speed of sound wave divided by 2 (go and back)
  return distance; 
}
void startServo(){

  Serial.println((String)distance);
  servo.write(180);

}




