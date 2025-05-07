
// project question 1 (for Q1 of lab 3)
// using lab 3 solution provided since it is clearer

float read_voltage(int pin){
  //variable is called by value since it isn't modified
  int analog_input0;
  float voltage0;
  analog_input0 = analogRead(pin); 
  voltage0 = analog_input0/1023.0*5;
  //two previous lines read analog input and convert it to volts
  return voltage0;  
}

float delta_voltage(float voltage0, float& min, float& max, float& delta){
  //voltage0 is called by value since it isn't modified by this function
  //min, max and delta are called by reference, because they are modified and kept to be printed out in the loop
  if(voltage0 > max) max = voltage0;
  if(voltage0 < min) min = voltage0;
  //since max and min will the final values on the last loop, we can include the calculation for delta
  //ideally would only be calculated at N=1000 using if(N=1000) and having N in input, but would make function less general
  delta= max - min;
}


void setup() {

  // serial communication 115200 bits per second
  Serial.begin(115200); 
}

void loop() {
  
//declaration and initialization of variables
  int N = 1000, i; //sample size of 1000
  
  float min, max, ave, sum, delta=0;
  //int analog_input0; //was worked into function
  float voltage0; 
  
//initializing for counts and comparisons
  min = 1.0e6; 
  max = -1.0e6; 
  sum = 0.0; 

  //for loop for 1000 sample size
  for(i=1;i<=N;i++) {
    //calling analog to voltage conversion function
    voltage0 = read_voltage(A0);  
      //Serial.print("\nvoltage0 = ");
      //Serial.print(voltage0,5); // print out to 5 decimal places
  
    sum += voltage0;
    
    //calling function to calculate min, max values and delta
    delta_voltage(voltage0, min, max, delta);

    //testing purposes
    //Serial.print("\nmax=");
    //Serial.print(max,5);
    //Serial.print("\nmin=");
    //Serial.print(min,5);
    //Serial.print("\ndelta=");
    //Serial.print(delta/2,5);

    //delay before starting loop
    delay(1); 
  }

  //calculating average
  ave = sum / N;
  
  //delta = max - min; //was worked into function
  
    //testing purposes
    //Serial.print("\nmax=");
    //Serial.print(max,5);
    //Serial.print("\nmin=");
    //Serial.print(min,5);

    //printing out values with delays to ensure the values are printed out completely
    Serial.print("\naverage voltage = ");
    Serial.print(ave,5);
    delay(50);
    Serial.print("\nestimate of noise level =");
    Serial.print(delta/2,5);
    delay(1000);



  exit(0); 
}
