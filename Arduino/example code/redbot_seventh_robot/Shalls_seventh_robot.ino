/***********************************************************************
RedBot Library_Test

Created 30 Jul 2013 by Jeff @ SparkFun Electronics.

This code is beerware- feel free to make use of it, with or without
attribution, in your own projects. If you find it helpful, buy me a beer
the next time you see me at the local- or better yet, shop SparkFun!


***********************************************************************/
//include the redbot library to get the functions out of the library
#include <RedBot.h>




// Instantiate the motor control class. This only needs to be done once
//  and indeed SHOULD only be done once!
RedBotMotor motor;



void setup()
{
  Serial.begin(9600);//This will open the serial port to send values out to calibrate sensors
  
  Serial.println("Hello world!");//This should print once to make sure you're getting serial communication
 
}

void loop()
{  

  int motorSpeed=(analogRead(A0)/4);
    motor.rightDrive(255);   // drive a bit
    motor.leftDrive(motorSpeed);
}
