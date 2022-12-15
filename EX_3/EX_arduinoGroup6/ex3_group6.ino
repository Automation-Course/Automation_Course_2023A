#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h> 
#include<IRremote.h>


unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
unsigned long buttonmillis;
const unsigned long period = 5000;
const unsigned long shortperiod = 1000;
bool em;
bool reg;
const byte redledPin = 7;    //using the built in LED
const byte greenledPin=8;
const byte buttonPin=12;
const byte servoPin=10;
const byte irPin=13;
IRrecv reciver(irPin);
decode_results rs;
int counter=0;
float duration;
float distance;
Servo servo1;


LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Serial.begin(9600);
  pinMode(redledPin, OUTPUT);
  pinMode(greenledPin, OUTPUT);
  pinMode(buttonPin,INPUT);
  startMillis = millis();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,3);
  lcd.print("No Passage");
  digitalWrite(redledPin,HIGH);
  servo1.attach(servoPin); 
  servo1.write(90);
  reciver.enableIRIn();

}

void loop()
{
  if(reciver.decode(&rs) and !em)
  {
    reciver.disableIRIn();
    Serial.println(rs.value,HEX);
    delay(2000);
     servo1.write(120);
     delay(1000);
     servo1.write(90);
    digitalWrite(greenledPin,HIGH);  
    digitalWrite(redledPin,LOW);
     lcd.clear();
    lcd.setCursor(0,3);
    lcd.print("Pass");
     delay(5000);
    digitalWrite(greenledPin,LOW);
    digitalWrite(redledPin,HIGH);
    delay(10); 
     lcd.clear();
    lcd.setCursor(0,3);
    lcd.print("No Passage");
     servo1.write(60);
     delay(930);
     servo1.write(90);
     reciver.enableIRIn();
     reciver.resume() ;
  }
  duration=pulseIn(9,HIGH);
  distance=duration*.0343/2;
   currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)

  if(digitalRead(buttonPin)==HIGH and !em)
  {
       reciver.disableIRIn();
       counter=counter+1;
    Serial.print("Emergency uses today ");
    Serial.println(counter);
    servo1.write(120);
     delay(1000);
     servo1.write(90);
    lcd.clear();
    lcd.setCursor(0,3);
    lcd.print("Emergency");   
    digitalWrite(redledPin,LOW);
     digitalWrite(greenledPin,HIGH);     
    em=true;
    delay(5000);
    lcd.clear();
    lcd.setCursor(0,3);
    lcd.print("No Passage");
    digitalWrite(redledPin,HIGH);
    digitalWrite(greenledPin,LOW);
    buttonmillis=currentMillis;
    em=false;
    servo1.write(60);
     delay(930);
     servo1.write(90);
     reciver.enableIRIn();
     reciver.resume() ;
  }
  
  
 
 }