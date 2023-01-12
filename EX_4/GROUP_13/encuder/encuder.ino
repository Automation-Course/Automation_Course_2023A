#include <PIDController.h>   
PIDController pid;

#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9
int motor_pwm_value;
int Power_In_Percents;

#include <Encoder.h>
#define ENCODER_A 2 
#define ENCODER_B 3 

float goal_deg; 
int encoder_count = 0; // stores the current encoder count
float tick_to_deg1 ;
Encoder myEnc(ENCODER_B, ENCODER_A);


/*******functions******/
float tick_to_deg(long tick){
    return tick*360.0/440.0;
  }

void get_user_input(){// gets the goal angle from the user
  goal_deg = (Serial.parseFloat());
  Serial.read();    // get the ENTER char from the serial
}  


double Kp;
double Kd;
double Ki;


void forward(){
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  }

void reverse(){
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
  }


void setup() {

   Serial.begin(9600);



 Kp = 5.5;
 Kd = 1.4;
 Ki = 1.6;


 goal_deg = 0;

pid.begin(); // Initialize the PID controller
pid.limit(-180, 180); // The PID output can be limited to values between -255 to 255
pid.tune(Kp, Ki, Kd); // Set PID parameters
pid.setpoint(goal_deg); // the goal angle

}

void loop() {

   if (Serial.available()>0){ // Wait for User to Input Data
     get_user_input();
    }

  encoder_count = myEnc.read();
  tick_to_deg1 = tick_to_deg(encoder_count);
  while (abs(tick_to_deg1)>360){
    if (tick_to_deg1<0)
        tick_to_deg1=tick_to_deg1+360;
    else
        tick_to_deg1=tick_to_deg1-360;       
  }

float distance= tick_to_deg1-goal_deg; 
// calculates the distance between what user asked and how far the angle from there
Serial.print("distance = ");
  Serial.println(distance);// shows in serial monitor the distance

tick_to_deg1= distance;
//when the angle is far from destenation, we need more speed too press for our goal
if (tick_to_deg1 < 30){
  if(tick_to_deg1<15){
    if(tick_to_deg1<11.46){
      if(tick_to_deg1<6){
        tick_to_deg1 = tick_to_deg1*4; 
      }  
      else tick_to_deg1 = tick_to_deg1*3;
    }
    else tick_to_deg1 = tick_to_deg1*2;
  }
  else tick_to_deg1 = tick_to_deg1*1.5 ;
} 
if(tick_to_deg1 > 85)
  tick_to_deg1 = 60;

motor_pwm_value = float(pid.compute(tick_to_deg1*1.5));  

   // calculate motor direction
  if (motor_pwm_value <0 )
    reverse();
  else 
   forward();
  
  // send PWM value to motor
  analogWrite(enA, abs(motor_pwm_value));
 
 delay(10);


}
