// Libraries.
#include <LiquidCrystal_I2C.h>// LCD package.
#include <Servo.h>// Servo package.
#include <Wire.h>// Allows to communicate with I2C device - a package.
#include <MQ2.h>// Gas sensor package. 
#include <OneWire.h>// Temperature package.
#include <DallasTemperature.h>// Temperature package.

// Digital. 
#define buzzerPin 4
#define yellowLedPin 7
#define greenLedPin 8 
#define servoPin 9 
#define redLedPin 11
#define ONE_WIRE_BUS 2// Data wire is plugged into pin 2 on the Arduino.

// Analog. 
#define gasSensor A0

// Temperature variables. 
float tempC = 0;
OneWire oneWire(ONE_WIRE_BUS);// Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature sensors(&oneWire);// Pass our oneWire reference to Dallas Temperature.

// Gas sensor variable.
int sensorMaxGas = 350;

// Servo variables.
Servo servo;
int angle = 0;
bool Direction = true;

// LCD definition.
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()// Setup code - run once for initialization.
{
  lcd.init();
  lcd.backlight();
  servo.attach(servoPin);
  Serial.begin(9600);
  sensors.begin();// Start up the library. 
  // Digital setup code.
  pinMode(buzzerPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  // Analog setup code.
  pinMode(gasSensor, INPUT);
}// End setup.

void loop()// The main loop that will run infinite times.
{
  if(tempC < 45){// Checks if the temperature is below 45 Celsius.
     spiningServoEngine();// Function that spining the servo, always work until the temperature is above 45 Celsius.
  }// End if.
  int analogGasValue = getAnalogGasValue();
  if(analogGasValue > sensorMaxGas)// Checks if there is a toxic gas in the area.
  {
    toxicAlarm();
  }// End if.
  else// There is not a toxic gas in the area.
  {
    freshAir();
  }// End else.
  sensors.requestTemperatures();// Temperature reading.            
  tempC = sensors.getTempCByIndex(0);// tempC will show the current temperature to Celsius.
  printTemperature(tempC);
  if(tempC > 45)// Checks if the temperature higher than 45. If it is - the yellow led will start flashing and the servo will stop working. 
  {
    highTemperature();
  }//End if.
}// End loop.

void spiningServoEngine()// Spining servo function.
{
  if (Direction){
   angle +=180;
  }else{
   angle -=180; 
  }
  servo.write(angle);
  if(angle == 180)Direction = false; 
  if(angle == 0)Direction = true;
}// End spiningServoEngine function.

int getAnalogGasValue(){// Function that getting gas value and print it to serial and it return the value of the gas. 
  int tempAnalogGasValue = analogRead(gasSensor);// Read gas value in the area.
  Serial.print("Gas Value = ");
  Serial.println(tempAnalogGasValue);
  Serial.println();
  return tempAnalogGasValue;
}// End getAnalogGasValue function.

void toxicAlarm(){// Function that start the process when there is a toxic gas in the area.
  Serial.println("GAS DETECTED!");// Prints to serial monitor.
  Serial.println();
  ledFlashing(redLedPin);
  digitalWrite(greenLedPin,LOW);// Green Led off.
  tone(buzzerPin,1000,10000);// Buzzer on.
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("DANGER! EVACUATE");// LCD alarm output.
  delay(500);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("TOXIC GAS FOUND");// LCD alarm output.
  delay(500);
}// End toxicAlarm function.

void freshAir(){// Function that indicates there is none of toxic gas in the area.
  digitalWrite(greenLedPin,HIGH);// Green Led on.
  digitalWrite(redLedPin,LOW);// Red Led off.
  noTone(buzzerPin);// Buzzer off.
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HAVE A NICE DAY");// LCD output.
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("ALL CLEAR");// LCD output.
  delay(1000);
}// End freshAir function.

void printTemperature(float temperature){// Function that get the temperature value and print it to the serial.
  Serial.print("TEMPRATURE = ");
  Serial.print(temperature);
  Serial.println("*C");
  Serial.println();
}// End printTemperature function.

void highTemperature(){// Function that indicates there is high temperature than the servo will stop and the yellow led will blink.
  servo.write(90);
  ledFlashing(yellowLedPin);
}// End highTemperature function.

void ledFlashing(int led)// Blinking led function.
{  
    digitalWrite(led, HIGH);// LED light on.
    delay(4);// Wait. 
    digitalWrite(led, LOW);// LED light off.
    delay(4);// Wait. 
}// End ledFlashing function.
