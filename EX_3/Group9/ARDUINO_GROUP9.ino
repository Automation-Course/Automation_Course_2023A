// C++ code
#include <Wire.h> 
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
//Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd_1(0x27,16,2); // הגדרה של מסך LCD
Servo Heater;// הגדרה של SERVO

//הגדרה לאיפה מחוברים הרכיבים המערכת
int Photoresistor= A3;
int GreenhouseLight=11;
int tempSensor = A0 ;
int servoPin = 3 ;

// הגדרת משתני התחלה 
int GreenhouseLightValue=0;
int GreenhouseLightBrightness;
double temp1 ;
double temp=25;
int inputTemp1 ;
int angle = 0;  //init servo not to move
bool Direction = true; 


void setup() {
  //initialize the LCD
  lcd_1.init();

  //turn on the blacklight and print a message
  lcd_1.backlight();

  lcd_1.begin(16, 2);
  // הגדרה פלטי קלט ופלט
  pinMode(tempSensor, INPUT); 
  pinMode(Photoresistor,INPUT);
  pinMode(GreenhouseLight,OUTPUT);

    Heater.attach(servoPin);
  Heater.write(0);
    Serial.begin(9600);

}

void loop()
{ 
  inputTemp1=analogRead(tempSensor); // קריאת ערך של חיישון הטמפרטורה
  temp = map(((inputTemp1/1024.0)*5-0.5)*100, 0, 1023, -50, 125); //  התאמת ערכים של חיישן טמפרטורה
  tempCheck(temp); // בודק מה הטמפרטורה וכיצד זה משפיע על אופן הפעולה שלנו
  delay(1000);

    GreenhouseLightValue = analogRead(Photoresistor);  // קריאת ערכים מחיישן אור 

   GreenhouseLightBrightness = map(GreenhouseLightValue, 679, 6, 255, 0); // התאמת ערכים של חיישון אור
      

if (GreenhouseLightBrightness<100){ // אם הערכים מתקבלים נמוכים מ100 אין צורך בתאורה נוספת
  analogWrite(GreenhouseLight, 0); 
}
else{
  	analogWrite(GreenhouseLight, GreenhouseLightBrightness); // יש צורך בתאורה נוספת ולכן תידלק הנורה
}

}

void tempCheck (double temp) // פונקציה של בדיקת הטמפרטורה
{
      
 
   if (temp < 22)// אם הטמפרטורה מתחת ל22 מתחיל לחמם
   {
     printScreen("Starting warming"); // כתיבה למסך LCD 
     startWarming(); // התחלת חימום
   }
	 if (temp >= 50)// מפסיקים לחמם 
    	{
        printScreen("Stoping warming"); // כתיבה למסך LCD
  	 	stopWarming(); // פונקציה של הפסקת חימום
    	}
	 if (temp > 21 and temp < 50 ){ //הטמפרטורה נמצאת בין הערכים התקינים ולכן לא יקרה דבר
  		
    		printScreen("Temp OK");
 		 }
}

void startWarming () // פונקציה הפעלת חימום
{
  if (Direction) { // משנה את הזוויות כדי ש servo ימשיך להסתובב
   	angle +=1;
  }
  else{
   	angle -=1; // משנה את הזוויות כדי ש servo ימשיך להסתובב
  }
  Heater.write(angle); //לתת פקודה לסרבו לפי  הזווית שניתנה לו
  if(angle == 180){ // אם הזויות שווה ל180 אז נקטין את ערך הזויות
  		Direction = false; 
  }if(angle == 90){ // אם הזויות שווה ל90 אז נקטין את ערך הזויות
    	Direction = false;
  }if(angle == 0){ // אם הזויות שווה ל0 אז נעלה את ערך הזויות
      Direction = true;
  }
   
}


void stopWarming () // הפסקת החימום
{
  angle = 0; // שינוי ערך הזויות ל0 כדי המנוע יפסיק לפעול
  Heater.write(angle); // כתיבת הערך מנוע
}
  
void printScreen (String print){ // פונקתיה הדפסה 
  lcd_1.setCursor(0, 1);
  lcd_1.print(print); // הדפסה במסך LCD
  lcd_1.setBacklight(1);
 
}

