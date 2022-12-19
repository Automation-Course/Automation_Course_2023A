#include <LiquidCrystal.h>

#//include <LiquidCrystal.h>
 #include <Wire.h>
//#include <Adafruit_LiquidCrystal.h> = for lcd simulation
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
 
 
#define tempSensor A1
#define smokeSensor A0
#define servoPin 9
#define ledPin 8
 
int temp;
int smoke;
int angle = 0;
LiquidCrystal_I2C lcd_1(0x27, 16, 2);
 
//Adafruit_LiquidCrystal lcd_1(0); for lcd simulation
Servo servo;
 
void setup()
{
   // initialize inputs and outputs
  //lcd_1.begin(16,2);
  lcd_1.init();
  lcd_1.backlight();
  pinMode(tempSensor, INPUT);
  pinMode(smokeSensor, INPUT);
  servo.attach(servoPin);
  Serial.begin(9600);
   digitalWrite(8,0);

  printScreen("Hello Eyal!",0,0);
 
   
}
 
void loop()
{
lcd_1.setCursor(0,1);
  //printScreen("test",1,0);

  //Loop of checking current weather
  temp=checkTemp(tempSensor);
  smoke=checkSmoke(smokeSensor);
  HowIsToday(temp,smoke);
 
}
// check temperature
int checkTemp (int tempSensor){
// int temp = map(((analogRead(tempSensor) - 20) * 3.04), 0, 1023, -40, 125);
 int temp=map(analogRead(tempSensor),0,1023,-400,600)/10;

 
    return temp;  
}
 
//Print function
void printScreen(String print,int x,int y){
  lcd_1.setCursor(x, y);
  lcd_1.print(print);
  lcd_1.backlight();
 
}
// check smoke level
int checkSmoke(int smokeSensor){
  int smoke = map(analogRead(A0),0,1023,0,255);

    return smoke;

}
void HowIsToday (int temp, int smoke){
  lcd_1.clear();
  //check how is the weather today according to temperature and smoke level
  if(smoke <=500){
   digitalWrite(8,LOW);
   if (temp>68 && temp<86){
        printScreen("Its a nice day",0,0);
            printScreen("go to the Park!",0,1);
        digitalWrite(8,0);
       }
    if(temp<=68 && temp>50){
        printScreen("a bit chilly",0,0);
          printScreen("take a sweater!",0,1);
          digitalWrite(8,0);
 
        }
    if(temp<=50){
        printScreen("freezing!stay at",0,0);
            printScreen("home and netflix",0,1);
          digitalWrite(8,0);
 
    }
    if(temp>=86){
        printScreen("its pool time!",0,0);
        TurnOnFan();
          digitalWrite(8,0);
         }
  }
  else{
    printScreen("Too much smoke -",0,0);
    printScreen("stay at home",0,1);
    lcd_1.clear();
    printScreen("and use less-",0,0);
    printScreen("plastic!!!!!!!!",0,1);
    digitalWrite(8,225);
  }

}
void TurnOnFan(){
  //turning on fan for hot day
if (angle <= 360){
   servo.write(angle);
   angle+=20;
  }else{
   servo.write(angle);
   angle-=20;
  }
}
 
 
 


