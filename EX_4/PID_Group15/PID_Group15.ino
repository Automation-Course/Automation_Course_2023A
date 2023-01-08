#include <Encoder.h>
#include <PIDController.h>


#define encoderPin1 2 
#define encoderPin2 3 // Encoder output to Arduino Interrupt pin ncoderPinB
const float kp = 1;
const float ki = 0;
const float kd = 0;
 float degree = 0.0;
const int motor_CW = 10;
const int motor_CCW = 11;
const int enA = 9;
Encoder encoder(encoderPin1,encoderPin2);
PIDController pidController;
double angle = 0.0; // current angle of the pendulum

void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(motor_CW, OUTPUT);
  pinMode(motor_CCW, OUTPUT);
  pidController.begin(); 
  pidController.limit(-180, 180); 
  pidController.tune(kp, ki, kd); 
  pidController.setpoint(degree); 

}

void loop() {
  // // Read encoder and calculate current angle of pendulum
  long encoderCount = encoder.read();
  angle = tick_to_deg(encoderCount);
   float control = pidController.compute(angle);
   Serial.print("angle: ");
   
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
  digitalWrite(motor_CW, HIGH);
  digitalWrite(motor_CCW, LOW);
  }

void reverse(){
  digitalWrite(motor_CW, LOW);
  digitalWrite(motor_CCW, HIGH);
  }