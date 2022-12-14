#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#define servoPin 9
// C++ code

LiquidCrystal_I2C lcd_1 (0x27,16,2);  
String serialRead;				//string value from serial monitor
int ledYellow = 8;              //Yellow Led
int ledRed = 7;               	//Red Led
int GasSensor = A0;				//Gas sensor
int GasValue = 0;				//the gas sensor value
int GasValuePercent = 0;		//the air pollution in percents
int Buzzer = 5;            	//Buzzer output
int Button = 10;             	//Button input
int angle = 0;                  //Servo angle
int ExtremeGasTime = 0;         //Time with Extreme Gas
int crowd = 5000;               //Number Of People in the concert
int buttonState = 0;            //Button State- Pressed or Not
int done = 4000;                //Flickering Time
bool StartShow = true; 		  	 //if show needs to start
bool GasConcentration = false;  //If Currently High Gas Concentration 
bool StartServo = false;		//if start servo 
bool ShowStarted = false;       //if show already started
bool SmokeSpread = false;       //if smoke has been spread
bool ExtremeGasConcentration = false;           //If Currently Extreme Gas Concentration 
bool Evacuate = false;         //if people need to be evacuated
bool Evacuated = false;         //if all people evacuated
bool Direction = true;          //Direction of servo rotation
Servo servo;                    //Servo Setting


void setup()
{ 
  lcd_1.init();
  lcd_1.backlight();
  Serial.begin(9600);          //initializing the printings to the serial monitor
  pinMode(GasSensor, INPUT);
  pinMode(Button, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  servo.attach(servoPin);
}

void loop()
{
  GasValue = analogRead(GasSensor);
  buttonState = digitalRead(Button);

  if((buttonState == HIGH)&& (StartShow)) {        //Start Show LCD
  digitalWrite(ledYellow, LOW);
  ShowStartsScreen();
  ShowStarted = true;
  StartShow = false;
  Evacuated = false;
  }

  GasValuePercent = map(GasValue, 200, 500, 0, 100);       //Converts Gas Value

  if((ShowStarted)&& (!SmokeSpread) && (GasValuePercent > 45)) {       //Smoke Spread For Avira
  SmokeSpread = activateSmokeFun(7, done);                      //Spreads Smoke for 4 Seconds;
  done -= 1000;
  }
  
  if(StartServo) {                 //Rotates Servo
    rotateServo ();
  }

  if((ShowStarted)&&(SmokeSpread)) {              //Show started and smoke has been spread
    delay(2000);                                 //Checks the Gas Concentration

    if ((GasValuePercent > 55)||(ExtremeGasConcentration)) {           //Extreme Gas Concentration
     if (GasConcentration == false) {                                  //First discovery of high gas
          ExtremeGasConcentration = true;
          updateHighGas ();
     }

      if (ExtremeGasTime < 5000) {                        //10 Seconds has yet to pass
        if(checkInvalid(GasValuePercent)) {
           ExtremeGasTime += 900;
        }
        else {
        backToNormal ();                     //Gas Precent is back to low
        printScreen ("Keep partying");
        } 
      }

      else {

       if(((checkInvalid(GasValuePercent))&& (!Evacuated)) || (Evacuate)) {             //Need to evacuate from the show
         Evacuate = true;
         printScreen ("Please Evacuate");
         tone(Buzzer, 1000);                                                          //Evacuation Buzzer 

         if (crowd > 0) {                                                             //Crowd leaving the show
           crowd = crowd - 1000;
          }

         else {                                                                    //all the crowd has left the show
           noTone(Buzzer);                                                         //Stop evacuation buzzer
           backToNormal();
           digitalWrite(ledYellow, HIGH);             				                      //Yellow Light when cleared
           printScreen ("Drink Aperol!");
           Evacuate = false;
           Evacuated = true;
          }

        }

      }
    }

   if((GasValuePercent > 50)&&(!ExtremeGasConcentration) && (ShowStarted))  {            //Alarming gas value- not extreme
     updateHighGas ();
    }

   if ((GasConcentration) && (GasValuePercent < 45) && (!Evacuate)) {                    //Gas Precent is back to low
    backToNormal();                              
    printScreen ("Keep partying");                     
    }
  }

}



//-----------Functions--------------

//Print To Screen
void printScreen (String toPrint)  {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print(toPrint);
  lcd_1.setBacklight(1);
  delay(1000); // Wait for 1 Second
}

//Show Starts Screen Print
void ShowStartsScreen () {
   printScreen("3");
   printScreen("2");
   printScreen("1");
   printScreen("Rock & Roll!");
}

//Activates Smoke For Vibes
bool activateSmokeFun (int led, int done)
{
  if (0 < done)
  {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
    return false;
  }
  done = 4000;
  digitalWrite(led, LOW);
  return true;
}

 //Operates Servo    
void rotateServo () {
    if(Direction) {
      angle += 1;
    }
    else {
      angle -= 1;
    }
    servo.write(angle);
    if(angle = 180) {
      Direction = false;
    }
    if(Direction = 0) {
      Direction = true;
    }
 }
       
//Checks if gas Concentration is invalid
bool checkInvalid (int gasValuePercent)
{ 
    if ((gasValuePercent < 45)&&(StartServo))
  {
    StartServo = false;
  }
  return StartServo;
}

//updates high gas measured
void updateHighGas () {
  GasConcentration = true;
  StartServo = true;
  digitalWrite(ledRed, HIGH);
}

//back to normal air
void backToNormal () {
  digitalWrite(ledRed, LOW);
  StartServo = false;
  ShowStarted = false;
  StartShow = true;
  SmokeSpread = false; 
  GasConcentration = false;
  ExtremeGasConcentration = false;  
  ExtremeGasTime = 0;   
  crowd = 5000;
  done = 4000;
}