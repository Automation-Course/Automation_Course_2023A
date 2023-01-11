#include <Encoder.h>
#include <PIDController.h>  

#define ENCODER_A 2 // encoder input
#define ENCODER_B 3 // encoder output
#define MOTOR_CCW 11 // against clock wise
#define MOTOR_CW 10 // clock wise
#define enA 9

float KP = 60;
float KD = 10;
float KI = 1;

int motor_pwm_value; 
int encoder_count = 0; // stores the current encoder count
float tick_to_deg1;
Encoder encoder(ENCODER_B, ENCODER_A);
PIDController PID;


void setup() {
  Serial.begin(9600);

  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);

  // Set initial rotation direction. assuming the motor initialized to spin clock wise
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  
  PID.begin(); // Initialize the PID controller
  PID.limit(-180, 180); // The PID output can be limited to values between -255 to 255
  PID.tune(KP, KI, KD); // Set PID parameters
  PID.setpoint(0); // the goal angle

 }
 

void loop() {
  encoder_count = encoder.read();
  float tick_to_deg1 = tick_to_deg(encoder_count); // the degrees from the encoder
  motor_pwm_value = float(PID.compute(tick_to_deg1)); // Calculate the pwm value for the motor using the degrees from the encoder read

  if (tick_to_deg1 <0 )
    reverse();
  else 
   forward();

  analogWrite(enA, abs(motor_pwm_value));
  delay(1);

  Serial.println(tick_to_deg1);
  
  }


float tick_to_deg(long tick){ // CONVERT TICKS FROM THE ENCODER TO DEGRIES
    return tick*360.0/440.0;
  }

void forward(){
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  }

void reverse(){
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
  }
 
