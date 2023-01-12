#include <Encoder.h>
#include <PIDController.h>    
#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB
#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9
PIDController pid;
int motor_pwm_value;
int encoder_count = 0; // stores the current encoder count
float tick_to_deg1=0;
float inputError;
//float error;
//int goalAngle=0;
Encoder myEnc(ENCODER_B, ENCODER_A);
/*******functions******/
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
 void getMotorV(){
 //  analogWrite(ENCODER_B,inputError/(360/440));
   motor_pwm_value = pid.compute(tick_to_deg1);
 }


/*******setup *******/
void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);
  // Set initial rotation direction
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
pid.begin(); // Initalize the PID controller
pid.limit(-180, 180); // The PID output can be limited to values between -255 to 255
pid.tune(1,0.11,0.1); // Set PID parameters
pid.setpoint(0); // the goal angle

 }
void loop() {
  encoder_count=myEnc.read();
  tick_to_deg1 = tick_to_deg(encoder_count);
 
  if(tick_to_deg1!=0){
    getMotorV();
  }
    //compute the PWM value for 					//the motor based on current angle
   Serial.println(tick_to_deg1);
   if( motor_pwm_value>0){
   reverse();}
   else{
   forward();
   }
   while (abs(tick_to_deg1)>360){
    if (tick_to_deg1<0)
        tick_to_deg1=tick_to_deg1+360;
    else
        tick_to_deg1=tick_to_deg1-360;       
  }

    // send PWM value to motor
  analogWrite(enA, (abs(motor_pwm_value)*255*4)/50);
  delay(1);   

    }
  
