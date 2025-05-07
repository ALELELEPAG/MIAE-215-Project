// project question 1 (for Q3 of lab 3)
// using lab 3 solution provided since it is clearer

//including servo library and creating servo object
#include <Servo.h> 

Servo servo1;  


float read_voltage(int pin){
  //variable is called by value since it isn't modified
  int analog_input0;
  float voltage0;
  analog_input0 = analogRead(pin); 
  voltage0 = analog_input0/1023.0*5;
  //two previous lines read analog input and convert it to volts
  return voltage0;  
}

void servo1_delay(int theta, int d){
  //both variables called by value since they aren't modified of printed out
  servo1.write(theta);
  delay(d);
  //moves servo1 and delays in one function
  //no output/reference variables since move executed in function
}

void minval(float voltage0, float& min, int theta1_d, int& theta1_d_min){
  //min and theta1_d_min are called by reference, since theta1_d_min is called in the loop function afterwards and min is carried in the for loop
  //voltage0 and theta_1d are called by value, since they are only inputted into this function
  //checking for minimums and assigning min values with if statement
  if(voltage0 < min) {
      min = voltage0;
      theta1_d_min = theta1_d; 
    }
    
}

void setup() {

  //connecting servo1 to pin 7
  servo1.attach(7);  

  // initialize serial communication at 115200 bits per second
  Serial.begin(115200); 
}

// first method from question 3
void loop() {

  //initializing variables
  int theta1_d; 
  float voltage0; 
  float min;
  // servo angle for minimum voltage / maximum light
  int theta1_d_min; 
  float t;
  

  //calling function servo1 delay to move servo to zero with 1000ms interval
  servo1_delay(0, 1000);

          
  //initializing min for comparisons      
  min = 1.0e6; 

  //for loop incrementing from 0 to 180 degrees
  for(theta1_d = 0;theta1_d<=180;theta1_d++) {

    //incrementing servo1 with delay of 50ms
    servo1_delay(theta1_d, 50);
    
    //reading analog input and converting it into volts
    voltage0 = read_voltage(A0); 

    // approximate value of t
    t = micros()*1.0e-6;  
  
    //calling function to check for minimum voltage and corresponding angle
    minval(voltage0, min, theta1_d, theta1_d_min);
  
    //testing
    //Serial.print("\n");
    //Serial.print(t);
    //Serial.print(","); // for csv file
    //Serial.print(voltage0);
    //Serial.print(","); // for csv file
    //Serial.print(theta1_d);
  }
              
  // move servo1 to the min voltage/max light position with delay of 1 second
  servo1_delay(theta1_d_min, 1000);

  //testing
  //Serial.print("\nmin angle=");
  //Serial.print(theta1_d_min);
  //Serial.print("\nmin=");
  //Serial.print(min);

  
  //delay of 10 seconds before exiting
  delay(10000);
  exit(0);
}
