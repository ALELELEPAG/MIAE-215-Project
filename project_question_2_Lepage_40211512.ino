// project question 2
//This program takes an input from the x-axis of the joystick and uses it to move the servo
//analog inputs will be converted into angles and then fed into the servo1_delay function

//including servo library
#include <Servo.h>

//declaring servo pins and value variables
int xAxisPin = A0;    
       

//defining servo object
Servo servo1;

int read_angle(int pin){
  //pin is called by value, since it is a pin number it isn't called in the program afterwards
  //reads analog value from x-axis of joystick
  int xVal= analogRead(pin);
  //this line converts the analog input from the joystick (0-1023 range) into an angle for the servo (0-180 range)
  //values are divided by 100 to stay within the arduin uno int range
  int angle=xVal/100*180/(1023/100);
  return angle;
}

//this function was built in question 1
void servo1_delay(int theta, int d){
  //both variables called by value since they aren't modified of printed out
  servo1.write(theta);
  delay(d);
  //moves servo1 and delays in one function
  //no output/reference variables since move executed in function
}

void setup() {
  
  //enabling serial communication at 115200 bits per second
  Serial.begin(115200);

  //setting servo1 to digital pin 7 
  servo1.attach(7);

  //calling servo1 delay function built earlier to set servo1 at 90 with a 1s delay
  servo1_delay(90, 1000);
}

void loop() {

  //initializing servo angles by calling the read_angle function
  int servo_angle;
  servo_angle = read_angle(A0);

  //print line used for testing
  Serial.println(servo_angle);

  //calling servo1_delay function to move servo to angle inputted with joystick with delay of 50ms
  servo1_delay(servo_angle, 50);

  //exit for testing purposes
  //exit(0);
}
