#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9

#include <Encoder.h>
#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB
#include <PIDController.h>

int motor_pwm_value;
int DesiredAngle;
int Power_In_Percents;
PIDController pid;

int encoder_count = 0; // stores the current encoder count
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

float tick_to_deg(long tick){
    return tick*360.0/440.0;
  }
/*הפעלת מנוע DC */
void get_user_input(){
  DesiredAngle = Serial.parseFloat(); /*שמירת נתונים שנקלטו בערוץ תקשורת*/
  Serial.read();  /*get the Enter char from the serial*/
  motor_pwm_value = DesiredAngle;

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
  Serial.print("write the angle you want to send to the motor");
  pid.begin(); // Initialize the PID controller
  pid.limit(-180, 180); // The PID output can be limited to values between -255 to 255
  pid.tune(2, 1, 0.01); // Set PID parameters
  pid.setpoint(0); // the goal angle
  }

void loop() {
    encoder_count = myEnc.read();
    Serial.print("encoder_count = ");
    Serial.println(encoder_count);
    if(Serial.available()>0) //wait for userto input data
      get_user_input();
    tick_to_deg1 = tick_to_deg(encoder_count);
    while (abs(tick_to_deg1)>360)
    {
    if (tick_to_deg1<0)
        tick_to_deg1=tick_to_deg1+360;
    else
        tick_to_deg1=tick_to_deg1-360;       
    } 
    Serial.print("tick_to_deg1 = ");
    Serial.println(tick_to_deg1);
    delay(1000);
   //Somewhere in the main loop
  motor_pwm_value = float(pid.compute(tick_to_deg1));  //compute the PWM value for the motor based on current angle
    Serial.print("motor pwn value: ");
    Serial.println( motor_pwm_value);

    // calculate motor direction
  if (motor_pwm_value <0 )
    reverse();
  else 
   forward();
  // send PWM value to motor
  analogWrite(enA, abs(motor_pwm_value)); 
  delay(1);
  }