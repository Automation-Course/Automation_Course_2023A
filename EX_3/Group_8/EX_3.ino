#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <Servo.h>

#define led 4
#define servo_pin 12
#define buzer_pin 9
#define PIR_pin 2


bool motion_indicator;
bool direction=true;
int angle =0;
int volume =0;
bool already_write_original=false;
bool already_write_alarm=false;
int counter_as_timer=30;

LiquidCrystal_I2C lcd_1(0x27, 16, 2);
Servo servo;

void setup()
{
  lcd_1.init();
  lcd_1.backlight();
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(buzer_pin, OUTPUT); 
  pinMode(PIR_pin, INPUT);   
  servo.attach(servo_pin);
  digitalWrite(PIR_pin, LOW);
 counter_as_timer=30;
}

void loop()
{

  //Serial.println("counter_as_timer");
  //Serial.println(counter_as_timer);

  if(counter_as_timer<10){
    counter_as_timer+=1;
    move_scarecrow();
    buzer_dimer();
    blink(motion_indicator);
  }
  else{
    motion_indicator= detect_motion();
    blink(motion_indicator);
    if(motion_indicator==true){
      alarm();
    }
    else{
      no_alarm();
    }
  }
}

void blink (bool motion_indicator){
  int speed =0;
  if (motion_indicator){
    speed=200;
  }
  else{
    speed=1000;
  }
  	digitalWrite(led, HIGH); // set the led on
    delay(speed); // wait for a second
    digitalWrite(led, LOW); // turn the LED off
    delay(speed); // wait for a second
}

bool detect_motion(){
  if (digitalRead(PIR_pin)==HIGH){
   Serial.println("high"); 
   return true; 
  }
  else{
   Serial.println("low"); 
   return false; 
  }
}

void alarm(){  
  if (!already_write_alarm){
    Serial.print("alarm");
    already_write_alarm=write_to_lcd('A',already_write_alarm);
  }
  already_write_original=false;
  move_scarecrow();
  buzer_dimer();
  counter_as_timer=0;
}

void no_alarm(){
  servo.write(90);
  if (!already_write_original){
    Serial.print("original");
    already_write_original=write_to_lcd('O',already_write_original);
  }
  already_write_alarm=false;
  noTone(buzer_pin);
}

void move_scarecrow(){
  if(angle==0 & counter_as_timer%4==0){
    servo.write(90);
    angle=180;
  }
  else if(angle==180 & counter_as_timer%4==0){
    servo.write(90);
    angle=0;
  }
  servo.write(angle);
}

void buzer_dimer(){
  if(volume>=1000){
    volume=100;
  }
  else{
    volume+=200;
  }  
  tone(buzer_pin,volume);
  delay(300);
	Serial.print(volume);
}
bool write_to_lcd(char type,bool already_write){
  if(type=='A'){
    lcd_1.clear();
    lcd_1.print("Stay away!");
    lcd_1.setCursor(0,1);
    lcd_1.print("group 7!");
  }
   if(type=='O'){
      lcd_1.clear();
  		lcd_1.print("Group 7 original");
   }
	already_write=true;
  return already_write;
}
  