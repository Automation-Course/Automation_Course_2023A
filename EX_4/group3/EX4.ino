#include <Encoder.h>
#include <PIDController.h>

const int PRINT_INTERVAL = 1000000;

// Declare constants for the encoder pins
const int encoderPinA = 2;
const int encoderPinB = 3;

// Declare constants for the motor control pins
const int motorPinA = 10;
const int motorPinB = 11;
const int pwmPin = 9;


// Declare constants for the PID controller
const float kp = 50;
const float ki = 0;
const float kd = 10;

// Declare variables for the encoder and motor
Encoder encoder(encoderPinB, encoderPinA);
PIDController pid;

int goal_degree;

void setup() {
  Serial.begin(9600);

  // Declare the goal angle for the pendulum
  // int goal_degree = 0;
  goal_degree = get_input_from_user();
  // Initialize the encoder and motor pins
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
  pinMode(pwmPin, OUTPUT);

  // Set initial rotation direction
  digitalWrite(motorPinA, HIGH);
  digitalWrite(motorPinB, LOW);

  pid.begin(); // Initialize the PID controller
  pid.setpoint(goal_degree); // Set the goal angle
  pid.limit(-90, 90); // The PID output can be limited to values between -255 to 255
  pid.tune(kp, ki, kd); // Set PID parameters
}

void loop() {
  // Read the current position of the encoder
  int encoderPos = encoder.read();

  // Use the PID controller to calculate the motor speed
  float motor_pwm_value = float(pid.compute(encoderPos));
  Serial.print(goal_degree);
  Serial.print(","); 
  Serial.println(encoderPos);

  // Clamp the motor speed to the range -255 to 255
  motor_pwm_value = constrain(motor_pwm_value, -255, 255);
  // Set the motor direction and speed using the H-bridge driver
  if (motor_pwm_value > 0) {
    digitalWrite(motorPinA, HIGH);
    digitalWrite(motorPinB, LOW);
    analogWrite(pwmPin, motor_pwm_value);
  } else {
    digitalWrite(motorPinA, LOW);
    digitalWrite(motorPinB, HIGH);
    analogWrite(pwmPin, -motor_pwm_value);
  }
}

bool user_have_entered_input(){
  return Serial.available() > 0;
}

int get_input_from_user(){
  Serial.println("Insert desired degree for the pendulum:");  
  bool valid_input = false;
  while (!valid_input){
    while (!user_have_entered_input()){}
    goal_degree = Serial.parseFloat();
    Serial.read();
    Serial.println("Your chosen degree is:");
    Serial.println(goal_degree);
    if (goal_degree >= -15 && goal_degree <= 15) {
      valid_input = true;
    } 
    else {
      valid_input = false;
      Serial.println("Input is not in valid range. try again!");  

    }
}
  return goal_degree;
}
