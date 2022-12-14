
#include <Servo.h>
#include <IRremote.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


#define RED_LED 13
#define GREEN_LED 12
#define IR_RECEIVE_PIN 3
#define DOOR_OPEN 1
#define DOOR_CLOSED 0
#define servoPin  9

const int trig = 6;
const int echo = 7;
long totaltime;
int distance;

bool door_state = DOOR_CLOSED;
Servo servo;

LiquidCrystal_I2C lcd_1(0x27, 16, 2);


IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

void setup()
{
  lcd_1.init();
  pinMode(IR_RECEIVE_PIN, INPUT);
  servo.attach(servoPin);
  pinMode(RED_LED,OUTPUT);			// set LED pin as output
  pinMode(GREEN_LED,OUTPUT);
  pinMode(trig, OUTPUT); 
  pinMode(echo, INPUT);
  servo.write(0);
  digitalWrite(RED_LED,HIGH);
  irrecv.enableIRIn();
  Serial.begin(9600);
  
}

void loop()
{
  
  //check for sensor distance trigger
  if(measure_distance_cm()<5)
  {

     printScreen("opening door.");
    open_door();
    delay(500);
    printScreen("select a floor.");
    delay(500);
    

  }
  else{
     //do nothing
  }
  
  
  if (irrecv.decode(&results)) {
     switch(results.value)
     {        
       case 16724175: printScreen("Floor 1.");  // Button 1
        			 	 
          			  lcd_1.begin(16, 2);
                  delay(500);
                      printScreen("moving.");
                       delay(2000);
                       printScreen("opening door.");
                        open_door();
                         delay(500);
                          printScreen("select a floor.");
                           delay(500);



          		 	  break;
          
       case 16718055: printScreen("Floor 2."); // Button 2  
                      
          			  lcd_1.begin(16, 2);
                  delay(500);
                      printScreen("moving.");
                      delay(2000);
                       printScreen("opening door.");
                        open_door();
                         delay(500);
                          printScreen("select a floor.");
                           delay(500);

                       
                      break;          
          
       case 16743045: printScreen("Floor 3.");  // Button 3
        			  
          			  lcd_1.begin(16, 2);
                  delay(500);
                      printScreen("moving.");
                      delay(2000);
                       printScreen("opening door.");
                        open_door();
                         delay(500);
                          printScreen("select a floor.");
                           delay(500);

                      break;
              
       default: Serial.println(results.value); 
     }  
            irrecv.resume(); // Receive the next value    

   }  
      
}


/////////////// Functions ////////////////

void open_door()
{
  servo.write(180);
  digitalWrite(GREEN_LED,HIGH);
  digitalWrite(RED_LED,LOW);
  door_state = DOOR_OPEN;
  delay(3000);
  close_door();
  Serial.println("opening door.");
   Serial.print("distance[cm]=");
 Serial.println(distance);
   delay(3000);
}

void close_door()
{
  servo.write(0);
  digitalWrite(RED_LED,HIGH);
  digitalWrite(GREEN_LED,LOW);
  door_state = DOOR_CLOSED;
}



double measure_distance_cm()
{
digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
totaltime = pulseIn(echo, HIGH);
distance= totaltime*0.034/2;
  
  return distance;
   
}



void printScreen(String print){
  lcd_1.setCursor(0, 1);
  lcd_1.print(print);
  lcd_1.setBacklight(1);
  delay(5); // Wait for 500 millisecond(s)
}
