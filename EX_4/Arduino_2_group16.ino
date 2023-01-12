#include <Encoder.h>
#include <PIDController.h> 
#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB
#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9

int motor_pwm_value;
int Power_In_Percents;

int encoder_count = 0; // stores the current encoder count
float tick_to_deg1 ;
Encoder myEnc(ENCODER_B, ENCODER_A);
PIDController pid;

/**functions***/
float tick_to_deg(long tick){
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
 

/**setup ****/
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
  pid.tune(400, 0, 1000); // Set PID parameters
  float goal_deg= 45.0;
  pid.setpoint(goal_deg); // the goal angle

 }

void loop() {    
  motor_pwm_value = 0;
  
  
  encoder_count = myEnc.read();

  float enc_deg = tick_to_deg(encoder_count);

  Serial.print(enc_deg);
  Serial.println("");
  
 while (abs(tick_to_deg1)>360){
    if (tick_to_deg1<0)
        tick_to_deg1=tick_to_deg1+360;
    else
      tick_to_deg1=tick_to_deg1-360;       
  }

  motor_pwm_value = float(pid.compute(enc_deg));  

  // calculate motor direction
  if (enc_deg <0 ) {
    forward();}
    analogWrite(enA, abs(motor_pwm_value));
  if(enc_deg > 0){
  reverse();}
  
  analogWrite(enA, abs(motor_pwm_value));

  
  
 
 
  
  delay(1);
  }
