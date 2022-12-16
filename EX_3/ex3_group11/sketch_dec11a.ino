
#define echo 2
#define trig 3
#define outA 8 //red led
#define outB 9 //green led
//servo
#include<Servo.h>
Servo s1;
///lcd
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
///button
int ButtonValue=0;
int Button=5;
float duration; //time taken by the pulse to return back
float distance=0; //one way distance traveled by the pulse

const int intruderDistance=150; // the minimum distance up to wich the sensor is able to sense....cm..
void setup()
{
  pinMode(trig,OUTPUT);
  pinMode(echo, INPUT);
  pinMode(outA, OUTPUT);
  digitalWrite(outA,LOW);
  pinMode(outA, OUTPUT);
  digitalWrite(outB,LOW);
  Serial.begin(9600);
  ////servo
  s1.attach(10);
  //lcd
  lcd.begin(16,2);
  lcd.setCursor(0,1);
  //button
  pinMode(Button, INPUT);
  

}

void loop()
{
  time_Measurment();
  distance=(float)duration*(0.0343)/2; 
  Serial.println(distance);
  alarm_condition();
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  //////servo
     for (int i=0; i<= 180; i+= 1)
     {
       s1.write(i);             
        delay(15);                     
     }
    
      for (int i=180; i>=0; i-= 1) 
      { 
        s1.write(i);            
        delay(15);                      
       }
  //button
  ButtonValue= digitalRead(Button);
  if(ButtonValue != 0){
      lcd.clear();
      lcd.setBacklight(1);
      delay(500);
  	  lcd.print("TEAM 11");
     lcd.setBacklight(0);
      delay(500);
  }
  else{
    lcd.clear();
  }
  ////print
  Serial.print("Distance: ");
  Serial.println(distance);
   	
}

void time_Measurment()
{
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
}

void alarm_condition()
{
  if (distance<= intruderDistance)
  {
    digitalWrite(outA ,HIGH);
    digitalWrite(outB ,LOW);
    //lcd
      lcd.clear();
      lcd.setBacklight(1);
      delay(500); // Wait for 500 millisecond(s)

 	    lcd.print("D A N G E R !!!!");
      

      lcd.setBacklight(0);
      delay(500); // Wait for 500 millisecond(s)
 	
	

  }
  else
  {
    digitalWrite(outA ,LOW);
    digitalWrite(outB ,HIGH);
    lcd.clear();
  }
}

