// ARDUINO CCODE - GROUP #1

// library
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Create a servo object 
Servo servo; 
// Create LCD
LiquidCrystal_I2C lcd_1(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//create veriables:
//For Buzzer:
int buzzer = 8;
// For Servo:
int servoPin = 3;
int angle = 0;
bool Direction = true;
// For LED:
bool Is_LED_OFF = true; 
int ledRed = 2;
//For UltraSonic:
int trigPin = 10;
int echoPin = 9;
//For Distance:
long duration, distance;

void setup()
{
  lcd_1.init(); // initialize the lcd 
  // Print a message to the LCD.
  lcd_1.backlight();
  // Blinking block cursor
  lcd_1.blink_on();
  
  //define:
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(buzzer, OUTPUT);
  servo.attach(servoPin); 
  Serial.begin(9600);
}

void loop()
{  
  UltraSonic();
  Distance_Calculation();
  lcd();  
  if(distance < 100){
    Scare_Bird();
  }
  else{
    hazara_lashigra(); // return to normal
  }
}


void UltraSonic(){
    // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

void Distance_Calculation(){
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
}

void lcd(){
    // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

   String disp = String(distance);
   
   lcd_1.clear();
   lcd_1.print("distance :"); // first line 
   lcd_1.setCursor(0, 1); // second line
   lcd_1.print(disp);
   lcd_1.print(" cm");
}

void Scare_Bird(){
  blink(ledRed);
  buzz(buzzer);
  Serv();
  delay(1000);
}

void hazara_lashigra(){
   tone(buzzer, 40000);     // Stop sound
   servo.write(90);    // Servo back to place
   digitalWrite(ledRed, LOW); // turn the LED off
}

void blink(int led)
{  
  if (Is_LED_OFF){
    digitalWrite(led, HIGH); // set the led on
    Is_LED_OFF = false;
  }else{ 
    digitalWrite(led, LOW); // turn the LED off
    Is_LED_OFF = true;
  }
}

void buzz(int some_Buzzer){
  tone(some_Buzzer, 1000); // Send 1KHz sound signal
}

void Serv(){ //Move Servo around
  if (Direction){
   angle +=180;
  }else{
   angle -=180; 
  }
  servo.write(angle);
  delay(15);
  if(angle == 180)Direction = false; 
  if(angle == 0)Direction = true;
}