// C++ code
#include <IRremote.h>
#include <Servo.h> 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo s1;

int RECV_PIN = 6;
int Bpin = 4;
int S ;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  lcd.begin();
  Serial.begin(9600);
  s1.attach(5);
  lcd.backlight();
  //lcd_1.begin(16,2);
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); 
  Serial.println("Project Started");
  
   pinMode(8,OUTPUT);
   pinMode(9,OUTPUT);
   pinMode(10,OUTPUT);
   pinMode(Bpin,INPUT);
   s1.write(0);

   lcd.setCursor(0,0);
   lcd.print("GROUP 17   ");
   s1.attach(5);
   delay(2000);
  
   lcd.setCursor(0,1);
   lcd.print("TV REMOTE PROJECT  ");
   Serial.println("SHOOT");
   s1.write(0);
  
}

void loop() 
{
   if (irrecv.decode(&results))
   {     
       int value = results.value; 
       irrecv.resume(); // Receive the next value

  
  
       if(value == -23971 ) {
            s1.write(90);
           digitalWrite(8,HIGH);
           digitalWrite(9,LOW);
           digitalWrite(10,LOW);
           lcd.setCursor(0,1);
           lcd.print("90 Dgree R led   ");
         }

        if(value == 25245 )
      {
           s1.write(173);
          digitalWrite(8,LOW);
          digitalWrite(9,HIGH);
          digitalWrite(10,LOW);
          lcd.setCursor(0,1);
          lcd.print("180 Dgree B led   ");
           
      }
  
    if(value == -7651 )
  {
        s1.write(60);
        digitalWrite(8,LOW);
        digitalWrite(9,LOW);
        digitalWrite(10,HIGH);
        lcd.setCursor(0,1);
        lcd.print("60 Dgree G led   ");
  }
  
}
    if(digitalRead(Bpin))
  {
        s1.write(0);
        digitalWrite(8,LOW);
        digitalWrite(9,LOW);
        digitalWrite(10,LOW);
        lcd.setCursor(0,1);
     lcd.print("0 Dgree led OFF   ");
  }
         
delay(50);
}