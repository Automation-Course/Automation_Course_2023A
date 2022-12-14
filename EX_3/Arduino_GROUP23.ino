#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);
int ServoPin = 9;
int Redled = 13;
int Greenled = 12;
int angle = 0;
bool Direction=true;
int Piezo = 6;
int triggerPin = 7;
int echoPin = 4;
long duration=0, cm=0;
Servo servo;



void setup() {

  pinMode(Redled, OUTPUT);
  pinMode(Greenled, OUTPUT);
  pinMode(Piezo, OUTPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(ServoPin);
  lcd.init();
  lcd.backlight();
  lcd.print("Distance is: ");
  Serial.begin(9600);

}

void loop() {
  // convert the time into a distance
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  cm = readUltrasonicDistance(triggerPin, echoPin)/58;
  printLCD(String(cm));
  if(cm>=5 && cm<=200){
    activateAlarmSystem();
  }
  else{
    deactivateAlarmSystem();
  }
  
  printSerialMonitor();

}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  //delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}


// function is activating servo.
void startServo(){
  if (Direction){ 
   angle +=1;
  }
  else{
   angle -=1; 
  }
   servo.write(angle);
   //delay(15);
  if(angle == 180)
    Direction = false; 
  if(angle == 0)
    Direction = true;
}

//function is activating buzzer
void startPiezo(){
  tone(Piezo, 100, 1000); // turn on buzzer
}

// function is printing for LCD screen
void printLCD(String print){
  lcd.setCursor(0, 1);
  lcd.print(print);
  lcd.print("cm");
  lcd.setBacklight(1);
  delay(5); // Wait for 500 millisecond(s)
}

// function is activating the alarm system.
void activateAlarmSystem(){
  digitalWrite(Greenled,LOW); // turn off green led
  digitalWrite(Redled,HIGH); // turn on red led
  startServo();
  startPiezo();
}

// function is deactivating the alarm system.
void deactivateAlarmSystem(){
  digitalWrite(Redled,LOW); //turn off red led
  digitalWrite(Greenled,HIGH); // turn on green led
  servo.write(90); // turn off servo
  noTone(Piezo); //deactivating buzzer
}

// printing to serial monitor
void printSerialMonitor(){
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
}
