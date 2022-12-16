#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define LED 2
#define PhotoRes A0
#define Buzzer 7
Servo Servo_Motor;
int servo_pos = 0;
int servo_direction_pin = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup()
{
  Serial.begin(9600);
  Servo_Motor.attach(3);
  pinMode(LED, OUTPUT);
  pinMode(PhotoRes, INPUT);
  pinMode(Buzzer, OUTPUT);
  lcd.init();
	lcd.backlight(); 
}

void loop()
{
  int photo_value = analogRead(PhotoRes);
  
  if(photo_value < 400){
   Servo_Motor.detach();
    digitalWrite(LED, LOW);
    digitalWrite(Buzzer, HIGH);
    lcd.clear();                  // clear display
  lcd.setCursor(0, 0);          // move cursor to   (0, 1)
  lcd.print("Good Morning!"); // print message at (0, 1)
  delay(500); 
}
   
  else {   
  Servo_Motor.attach(3);
  digitalWrite(LED, HIGH);
  digitalWrite(Buzzer, LOW);
  delay(700);
  digitalWrite(Buzzer, HIGH);
  Servo_Motor.write(180);
  lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("Good Night!"); 
  
  }
  Serial.println(photo_value);
}