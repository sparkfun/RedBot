/***********************************************************************
RedBot Library_Test

Created 30 Jul 2013 by Mike Hord @ SparkFun Electronics.

This code is beerware- feel free to make use of it, with or without
attribution, in your own projects. If you find it helpful, buy me a beer
the next time you see me at the local- or better yet, shop SparkFun!

This is a simple hardware/library use demo for the RedBot. All it does
is print accelerometer and sensor data over the serial port, while
waiting for a tap on the accelerometer. When the accelerometer is tapped,
it drives forward a few inches.
***********************************************************************/
//include the redbot library to get the functions out of the library
#include <RedBot.h>




// Instantiate the motor control class. This only needs to be done once
//  and indeed SHOULD only be done once!
RedBotMotor motor;

int motorSpeed=100;
int grow=5;
void setup()
{
  Serial.begin(9600);//This will open the serial port to send values out to calibrate sensors
  
  Serial.println("Hello world!");//This should print once to make sure you're getting serial communication
 
}

void loop()
{  

  {
    motor.drive(motorSpeed);   // drive a bit
  
    delay(2);         // wait for stop to finish
    motorSpeed=motorSpeed+grow;
    if (motorSpeed>=255||motorSpeed<=100)
    {
     grow=grow*-1; 
    }
   
  }
  
  delay(500);
}
