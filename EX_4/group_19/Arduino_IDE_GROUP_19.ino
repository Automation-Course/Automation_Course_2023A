// Libraries.
#include <Encoder.h>// Encoder defining.
#include <PIDController.h>// PID Defining.

// Digital.
#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB.
#define MOTOR_CCW 11// Motor defining.
#define MOTOR_CW 10
#define enA 9

// K's Parameters.
float Kp = 1;
float Ki = 0.15;
float Kd = 5;

// Parameters.
float motor_pwm_value = 0;
float User_Input;
float encoderCount = 0;
float encoder_count = 0;
float tick_to_deg1 = 0;
float Motor_output = 0;

// PID.
PIDController pid; // Create an instance of the PID controller class, called "pid".

// Encoder.
Encoder myEnc(ENCODER_A, ENCODER_B);

/**Setup **/
void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);
  pid.begin();// Initialize the PID instance.
  pid.limit(-180, 180);// Limit the PID output between 0 and 255, this is important to get rid of integral windup!
  pid.tune(Kp, Ki, Kd);// Tune the PID, arguments: kP, kI, kD.
  pid.setpoint(User_Input);// The "goal" the PID controller tries to "reach". 
  Serial.print("Enter the degree between -15 to +15 degrees:");
}

/**LOOP**/
void loop() {  
  if (Serial.available()>0){// Wait for User to Input Data
    User_Input = Serial.parseFloat();
    if(User_Input>15){// Checks if the angle above 15. 
      User_Input = 15;
    }
    if(User_Input<-15){// Checks if the angle under -15.
      User_Input = -15;
    }
    Serial.read();// Get the ENTER char from the serial.
    pid.setpoint(User_Input);// The "goal" the PID controller tries to "reach".
    //Serial.print("The goal angle is: ");
    Serial.println(User_Input);
 }  
  encoderCount = get_degree();// Getting the current angle.
  //Serial.print("The current angle is: ");
  Serial.println(encoderCount);
  motor_pwm_value = pid.compute(encoderCount);// Compute the PWM value for the motor based on current angle. 
  Motor_output = abs(255*motor_pwm_value*4/100);// Calculate the PWM that will send to the DC motor.   
  if (motor_pwm_value > 0.0) {
    forward();
  } else {
    reverse();
  }
  analogWrite(enA, Motor_output);// Send PWM value to motor.
  delay(2000);  
}

/**functions**/
 float get_degree()// The function returns the current angle.
{
  encoder_count = myEnc.read();
  tick_to_deg1 = tick_to_deg(encoder_count);
  return tick_to_deg1;
}

float tick_to_deg(long tick){// The function calculates the current angle.
  return tick*360.0/440.0;
}

void forward(){// Function that sending to the motor to spin with clock direction.
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
}

void reverse(){// Function that sending to the motor to spin against clock direction.
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW,HIGH);
}