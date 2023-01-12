#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9
#include <Encoder.h>
#include <PIDController.h>    
#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin encoderPinB
int encoder_count = 0; // stores the current encoder count
float tick_to_deg1 ;
Encoder myEnc(ENCODER_B, ENCODER_A);
int motor_pwm_value;
int Power_In_Percents;
PIDController pid;
float Kp = 6.3052;
float Ki = 0;
float Kd = 0.04716;
int goal_deg = 0;
int wantedDegrees = 0;

/*******setup *******/
void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);

  // Set initial rotation direction
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  pid.begin(); // Initialize the PID controller
  pid.limit(-180, 180); // The PID output can be limited to values between -255 to 255
  pid.tune(Kp, Ki, Kd); // Set PID parameters
  pid.setpoint(goal_deg); // the goal angle
}


void loop() {

  Serial.print("Write the degrees you want to reach");
  
 if (Serial.available()>0){ // Wait for User to Input Data
    get_user_input();
  }
  
 delay(1);

  encoder_count = myEnc.read();
  Serial.print("encoder_count = ");
  Serial.println(encoder_count);
  tick_to_deg1 = tick_to_deg(encoder_count);

  motor_pwm_value = float(pid.compute(tick_to_deg1));  //compute the PWM value for 					//the motor based on current angle

  // send PWM value to motor
  analogWrite(enA, motor_pwm_value);

  pid.setpoint(wantedDegrees); // the goal angle

  Serial.print("tick_to_deg1 = ");
  Serial.println(tick_to_deg1);
  delay(1000);

  }






/*******functions******/
void forward(){
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  }

void reverse(){
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
  }
 
 void get_user_input(){
  wantedDegrees = Serial.parseFloat();
  Serial.read();    // get the ENTER char from the serial
}  

float tick_to_deg(long tick){
    return tick*360.0/440.0;
  }


