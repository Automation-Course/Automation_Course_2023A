
#include <Encoder.h>
#include <PIDController.h>

PIDController pid;

float Ki=0.1;
float Kp=1.2;
float Kd=0.4;

#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB
int encoder_count = 0; // stores the current encoder count
float tick_to_deg1 ;
Encoder myEnc(ENCODER_B, ENCODER_A);

#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9
float motor_pwm_value;



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
 



void setup(){
     Serial.begin(9600); //needed??????????????????
pid.begin(); // Initialize the PID controller

pid.limit(-180, 180); // The PID output can be limited to values between -255 to 255
pid.tune(Kp, Ki, Kd); // Set PID parameters
pid.setpoint(0); // the goal angle

  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);


}

void loop(){
  encoder_count = myEnc.read();
  Serial.print("encoder_count = ");
  Serial.println(encoder_count);
  tick_to_deg1 = tick_to_deg(encoder_count);
  while (abs(tick_to_deg1)>360){
    if (tick_to_deg1<0)
        tick_to_deg1=tick_to_deg1+360;
    else
        tick_to_deg1=tick_to_deg1-360;       
  }
  Serial.print("tick_to_deg1 = ");
  Serial.println(tick_to_deg1);
  //delay(5);



//keep changing and fixing:
if (abs(tick_to_deg1)>15){
  motor_pwm_value = float(pid.compute(tick_to_deg1)); //compute the PWM value for //the motor based on current angle


 
    if (tick_to_deg1<180){// && tick_to_deg1>15){
        reverse();}

    else{forward();}


  analogWrite(enA, abs(motor_pwm_value*255*30/360));
  

  }
else  {
  analogWrite(enA,0);}

 delay(20);
  }

