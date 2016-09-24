/****************************************
Visualizing Noise
credits to jayanth 
****************************************/

#include <Servo.h> 
int Noisepin= A0;    //sound sensor on analog pin A0
int sensorValue=0;    //variable to store value coming from sensor (good practice to do this)
int outValue=0;
Servo servo1;     //create servo object to control servo 1 (white wire)
Servo servo2;     //servo 2 (yellow wire) control object

const int sampleWindow = 50; // Sample window width in mS (250 mS = 4Hz)

// put setup code here, to run once:
void setup() 
{
  Serial.begin(9600);   //initialize serial communication at 9600 bits per second(bps):
  servo1.attach(9);    
  servo2.attach(8);
}

// put main code here, to run repeatedly:
void loop() 
{
  long sum = 0;
  unsigned long start= millis();  // Start of sample window
  while (millis() - start < sampleWindow)
{
    sensorValue= analogRead (Noisepin);   //analogRead takes value and puts it on 0-1023 values
    sum += sensorValue;
}
  
  float voltage = (sum *100/1023.0);    //multiplying the sensitivity by 100 
  //Serial.print(voltage);
  //Serial.print(" ");
  outValue = map (voltage, 8000,12000, 0, 180);   //scale to use with servo (value between 0 and 180)
    Serial.println (outValue); //-20 is to eliminate background noise 

  if (outValue*800>0) {
  servo1.write (outValue);     //sets servo1 position according to the scaled value
  servo2.write (outValue);
  
  }
  //delay (30);     //wait 30ms for servo to get there
}
