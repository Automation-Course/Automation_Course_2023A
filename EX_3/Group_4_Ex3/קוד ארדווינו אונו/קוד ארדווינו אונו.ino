// C++ code
//libraries
#include <Servo.h> //servo library
#include <Wire.h>//LCD library
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// define pins 
#define Echo_PIN 2 //echo
#define Trig_PIN 3 //trig
#define Led_PIN 4//led
#define RST_PIN 6 //reset servo
#define Buzzer_PIN 7 //buzeer

//define variables
const int scan_Distance = 100;//distance which the sensor sholud scan
int max_dist = 50; //distance which the sensor sholud detect 
Servo servo;
int speed = 0;
float duration;//time taken by the pulse to return back
float distance;//oneway distance travel by the pulse


void setup()
{
  //define I/O
  servo.attach(6);
  pinMode(Led_PIN, OUTPUT);
  pinMode(Trig_PIN, OUTPUT);
  pinMode(Echo_PIN, INPUT);
  pinMode(Buzzer_PIN, OUTPUT);

  digitalWrite(Buzzer_PIN, HIGH);
  lcd.init();//turn on the lcd
  Serial.begin(9600);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("    GROUP 4"); 
  delay(2000);
  lcd.clear();
  lcd.print(" Made With Love");
  lcd.setCursor(0,1);
  lcd.print("   To Eyal <3");
  delay(3000);
  lcd.clear();
  servo.write(90);

}

void loop()
{
  ultrasonic_scanning();
  scanning_on_off();
  
  if (distance <= max_dist){//activate alaram and servo only if the distance is smaller than 50 cm
    objects_detected();
  }
  else{
    digitalWrite(Buzzer_PIN, HIGH);// turn off buzzer
  }
  set_servo();
}

void scanning_on_off()// scans if doesnt detect object in max dist
{
  digitalWrite(Led_PIN, HIGH);
  if(distance > max_dist){
  servo.write(90);
  lcd.backlight();//turn on the lcd
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SCANNING..");
  }
}

void ultrasonic_scanning()// ultrasonic start scanning 
{
    digitalWrite(Trig_PIN, LOW);
    delayMicroseconds(2);
  
    digitalWrite(Trig_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_PIN, LOW);
  
    duration = pulseIn(Echo_PIN, HIGH);
    distance = (duration*(0.034))/2;// calculate the distance by the time takes the pulse to return
}
  
void objects_detected()//if an object is detected by the ultrasonic sensor write to lcd
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Eyal at ");
    lcd.setCursor(0, 1);
    lcd.print("    ");
    lcd.print(distance);
    lcd.print(" cm");
    if (distance <= max_dist){// if doesnt detect an object 
      digitalWrite(Buzzer_PIN, LOW);//turn on buzzer!! (although it doesnt seems like it)
    }
 
  }

void set_servo()// servo will start or stop running 
{
  if(distance>max_dist){
 	 speed = 90;
  }
  else{
  	speed = 150;
  }
  servo.write(speed);
}




                     
                     