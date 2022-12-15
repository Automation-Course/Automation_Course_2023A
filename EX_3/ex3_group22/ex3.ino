#include <IRremote.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

bool doorOpen ; 
bool doorlocked = true;
int IRpin = 11;  // pin for the IR sensor
int MiniReed = 2; // magnetic sensor
int buzzer = 4; // buzzer pin 
int led = 7;  //led pin
int serv = 9;  //servo pin


IRrecv irrecv(IRpin);
decode_results results;
Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16,2);


void setup()
{
 Serial.begin(9600);
 irrecv.enableIRIn(); // Start the receiver
 myservo.attach(serv);  // attaches the servo on pin 9 to the servo object
 pinMode (MiniReed, INPUT);
 lcd.init();
 lcd.backlight();
 lcd.setCursor(0, 0);
 pinMode (buzzer,OUTPUT);
 pinMode (led,OUTPUT);
  
}

void loop() 
{
  doorOpen = digitalRead (MiniReed) ;

  if(!doorOpen)
  {// if the door is closed- turn off the buzzer and the led
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, LOW);
    lcd.setCursor(0, 0);       
  } 
          
  if(!doorOpen and doorlocked) 
  {//the door is closed and locked
    lcd.print("door is locked                 ");
    Serial.println("door is locked   ");
    
    if (irrecv.decode(&results))// if there is a signal from the remote controll 
    {
      if(results.value==16730805){
        lcd.setCursor(0, 0);                
        lcd.print("unlocking now                 ");
        Serial.println("unlocking now");
        open();
        delay(2000);         
      }
    irrecv.resume()  ;      
    }          
  }  
    

  doorOpen = digitalRead (MiniReed) ;


  if(!doorOpen and !doorlocked) 
  { //if the door is closed but not locked yet
      lcd.setCursor(0, 0);                
        lcd.print("locking now                 ");
        Serial.println("locking now");
      close();          
  }                     
  
  if(doorOpen)
  {// turn alarm and and buzzer if the door is open
    lcd.setCursor(0, 0);
    lcd.print("close the door         ");
    Serial.println("the door is open");
    digitalWrite(buzzer, LOW);
    digitalWrite(led, HIGH);  
    }
   
  
} 

void open()
{//open the lock with servo
  if(!doorOpen){
   delay(50);
   myservo.write(0);
        delay(1000);
        myservo.write(90);
        delay(10);
        doorlocked = false;
  }
}

void close(){
  //close the lock with servo
  if(!doorOpen){
    delay(500);
    myservo.write(180);
        delay(1000);
        myservo.write(90);
        delay(10); 
        doorlocked =true;
}}
