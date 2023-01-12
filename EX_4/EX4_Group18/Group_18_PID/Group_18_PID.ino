
#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9
#include <PIDController.h>    // https://github.com/DonnyCraft1/PIDArduino
#include <Encoder.h>
#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin encoderPinB

PIDController pid;

float tick_to_deg1;
float encoder_count=0;
float enc_deg=0;
int motor_pwm_value;
int Power_In_Percents;
int userInput;
int userInput_help;
Encoder myEnc(ENCODER_B, ENCODER_A);
//PID constant
float Kp=15;
float Ki=2;
float Kd=1;

/*******functions******/

float tick_to_deg(long tick){ 
  return tick*360.0/440.0;    
}

void forward(){ //turn the motor clockwise
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
}
  

void reverse(){ //turn the motor Counterclockwise
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
}
 
 void get_user_input(){ //get the wanted degree from the user and enforce possible degree

  userInput_help = Serial.parseFloat();  // the goal angle
  Serial.read();    // get the ENTER char from the serial

}  

/*******setup *******/
void setup() {
  //define pins
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);

  // Set initial rotation direction
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);

pid.begin(); // Initialize the PID controller
pid.limit(-180, 180); // The PID output can be limited to values between -255 to 255
pid.tune(Kp, Ki, Kd); // Set PID parameters - Kp,Ki,Kd
pid.setpoint(0);
Serial.print("Write the angle you want to send to the motor");
}

void loop() {
 
    Serial.println(enc_deg);

    if (Serial.available()>0){ // Wait for User to Input Data
        get_user_input();
        if(userInput_help<-15 || userInput_help>15)
            Serial.print("Please write angle between -15 degrees to 15 degrees");
        else 
            userInput = userInput_help;
    }

// convert to real degree 
  encoder_count = myEnc.read();
  enc_deg = tick_to_deg(encoder_count);
  
  if (abs(enc_deg)>360){//keep the angle in the range -360 to 360 deegres
      if (enc_deg<0)
          enc_deg=enc_deg+360;
      else
          enc_deg=enc_deg-360;       
  }

  motor_pwm_value = float(pid.compute(enc_deg));  //compute the PWM value for 

  //the motor based on current angle
  if (enc_deg>userInput)  //choose the direction to rotate
      forward();
  else 
      reverse();
  
  // send PWM value to motor
  analogWrite(enA, abs(motor_pwm_value));
  delay(1);
  }


