#include <Encoder.h>
#include <PIDController.h>
#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9
#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB  
PIDController pid;
int encoder_count = 0; // stores the current encoder count
float tick_to_deg1 ;
int motor_pwm_value;
int Power_In_Percents;
int Kp =7.9;
int Ki = 0.7;
int Kd =3.8;
float goal_deg = 0;


Encoder myEnc(ENCODER_B, ENCODER_A);

void setup() {

  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);

  // Set initial rotation direction
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  
  
pid.begin(); // Initialize the PID controller
pid.limit(-255, 255); // The PID output can be limited to values between -255 to 255
pid.tune(Kp, Ki, Kd); // Set PID parameters
pid.setpoint(goal_deg); // the goal angle
Serial.println("Write your goal degree");


  }
  void loop() {
    
if (Serial.available()>0){ // Wait for User to Input Data
enterDeg();
if(goal_deg<-15 ||goal_deg>15) {
Serial.println("Please enter the degree again");
} 
}

  Serial.print("the goal degree is:");
  Serial.println(goal_deg);
  delay(1);
  encoder_count = myEnc.read();
  Serial.print("encoder_count = ");
  Serial.println(encoder_count);
  tick_to_deg1 = tick_to_deg(encoder_count);
  Serial.print("tick_to_deg1 = ");
  Serial.println(tick_to_deg1);
      while (abs(tick_to_deg1)>360){//keep the angle in the range -360 to 360 deegres
    if (tick_to_deg1<0)
        tick_to_deg1=tick_to_deg1+360;
    else
        tick_to_deg1=tick_to_deg1-360;       
  }
  motor_pwm_value = float(pid.compute(tick_to_deg1));
   // calculate motor direction
  if(motor_pwm_value<0)
    reverse();
  else
    forward();
  
  analogWrite(enA, abs(motor_pwm_value));
   Serial.println("Enter the goal degree:");
  delay(10);
  
}


float tick_to_deg(long tick){
    return tick*360.0/440.0;
  }
void enterDeg(){
goal_deg = Serial.parseFloat();
  Serial.read();
}

void forward(){
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  }
void reverse(){
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
  }