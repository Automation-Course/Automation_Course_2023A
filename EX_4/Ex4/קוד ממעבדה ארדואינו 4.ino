#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9
int motor_pwm_value =0;
float desired_deg;
#include <Encoder.h>
#include <PIDController.h>
unsigned long currentTime, previousTime;
double dt;
#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin encoderPinB
PIDController pid;
int encoder_count = 0; // stores the current encoder count, how many polses counted
float tick_to_deg1 ;
Encoder myEnc(ENCODER_B, ENCODER_A);


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
  desired_deg = Serial.parseFloat();
  Serial.read();    // get the ENTER char from the serial
  pid.setpoint(desired_deg); // the goal angle
}  

float tick_to_deg(long tick){
    return tick*360.0/440.0;
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
  
  Serial.print("Write the degree, you want to set to the motor");
  pid.begin(); // Initialize the PID controller
  pid.limit(-255, 255); // The PID output can be limited to values between -255 to 255-WHY?
  pid.tune(7,2.5, 2); // Set PID parameters

  }
void loop() {
  ///1//
  if (Serial.available()>0){ // Wait for User to Input Data
    get_user_input();  
  }
  // Your code here
    encoder_count = myEnc.read();
    tick_to_deg1 = tick_to_deg(encoder_count);
    while (abs(tick_to_deg1)>360){//make the value be less than 360 and bigger than 0
      if (tick_to_deg1<0)
          tick_to_deg1=tick_to_deg1+360;
      else
        tick_to_deg1=tick_to_deg1-360;       
    }
 
  Serial.println(tick_to_deg1);
  delay(1);
  motor_pwm_value = float(pid.compute(tick_to_deg1));  //compute the PWM value for 	//the motor based on current angle
  if (motor_pwm_value <0 )
    forward();

  else if(motor_pwm_value>0)
    reverse();
  // send PWM value to motor

  analogWrite(enA, abs(motor_pwm_value));
  
  }
