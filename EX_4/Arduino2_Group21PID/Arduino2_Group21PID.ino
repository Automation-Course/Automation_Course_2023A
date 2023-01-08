#include <Encoder.h>
#include <PIDController.h>

// Motor pins
const int motorPin1 = 10;
const int motorPin2 = 11;
const int enA = 9;

// Encoder pins
const int encoderPin1 = 2;
const int encoderPin2 = 3;

// PID constants
const float kp = 1;
const float ki = 0.17;
const float kd = 0.13;
const float goal_deg = 0.0;

// Global variables
Encoder encoder(encoderPin1,encoderPin2);
PIDController pidController;
double angle = 0.0; // current angle of the pendulum

void setup() {
  // Initialize motor pins as output
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pidController.begin(); // Initialize the PID controller
  pidController.limit(-180, 180); // The PID output can be limited to values between -255 to 255
  pidController.tune(kp, ki, kd); // Set PID parameters
  pidController.setpoint(goal_deg); // the goal angle

}

void loop() {
  // // Read encoder and calculate current angle of pendulum
  long encoderCount = encoder.read();
  angle = tick_to_deg(encoderCount);

  // // Calculate control signal
   double control = pidController.compute(angle);
   //Serial.print("angle: ");
   
   Serial.println(angle);

  if (control > 0.0) {
    forward();
  } else {
    reverse();
  }
  //Send pwm power to motor
  analogWrite(enA, abs(255*control*4/100)); 
}
//Convert ticks to degrees
float tick_to_deg(long tick){
    return tick*360.0/440.0;
}

void forward(){
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  }

void reverse(){
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  }
 