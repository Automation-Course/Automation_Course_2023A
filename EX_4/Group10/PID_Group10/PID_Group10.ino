#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9
#include <PIDController.h>
#include <Encoder.h>
#define ENCODER_A 2
#define ENCODER_B 3  // Encoder output to Arduino Interrupt pin ncoderPinB
PIDController pid;
int encoder_count = 0;  // stores the current encoder count
float Kp = 7.6;
float Ki = 2;
float Kd = 3;
float tick_to_deg1;
int motor_pwm_value;
int goal_deg = 0;
Encoder myEnc(ENCODER_B, ENCODER_A);


/*******setup *******/
void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);

  // Set initial rotation direction
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  pid.begin();             // Initialize the PID controller
  pid.limit(-180, 180);    // The PID output can be limited to values between -255 to 255
  pid.tune(Kp, Ki, Kd);    // Set PID parameters
  pid.setpoint(goal_deg);  // the goal angle
  Serial.println("Write the degrees you want to reach");
}


void loop() {
  if (Serial.available() > 0) {  // Wait for User to Input Data
    get_user_input();
    pid.setpoint(goal_deg);  // the goal angle
  }
  Serial.print("The goal degree = ");
  Serial.println(goal_deg);
  delay(1);

  //convert to real degree
  encoder_count = myEnc.read();               //reads the value from the encoder
  tick_to_deg1 = tick_to_deg(encoder_count);  //converts the degrees

  while (abs(tick_to_deg1) > 360) {  //keeps the angle in the range of -360 to 360 deegres
    tick_to_deg1 = rangeAngle(tick_to_deg1);
  }

  Serial.print("The current degree = ");
  Serial.println(tick_to_deg1);

  motor_pwm_value = float(pid.compute(tick_to_deg1));  //compute the PWM value for the motor based on current angle

  // calculate motor direction
  if (motor_pwm_value < 0) {  //choose the direction to rotate
    reverse();
  } else {
    forward();
  }

  //send PWM value to motor
  analogWrite(enA, abs(motor_pwm_value));

  delay(1);
}


/*******functions******/
//rotats clockwise
void forward() {
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
}

//rotats counter clockwise
void reverse() {
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
}

//keeps the angle in the range of -360 to 360 deegres
float rangeAngle(float degree) {
  if (degree > 0)
    degree = degree - 360;
  else
    degree = degree + 360;
  return degree;
}

//converts from ticks to degrees
float tick_to_deg(long tick) {
  return tick * 360.0 / 440.0;
}

//gets the wanted degrees from the user
void get_user_input() {
  goal_deg = Serial.parseFloat();
  Serial.read();  // get the ENTER char from the serial
  while (abs(goal_deg) > 360)
    goal_deg = rangeAngle(goal_deg);
}
