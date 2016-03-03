/***********************************************************************
 * Exp9_SerialDrive -- RedBot Experiment 9
 * 
 * The first step to controlling the RedBot remotely is to first drive it 
 * from the Serial Monitor in a tethered setup. 
 *
 * Hardware setup:
 * After uploading this sketch, keep the RedBot tethered to your computer with 
 * the USB cable. Open up the Seral Monitor to send commands to the RedBot to 
 * drive. 
 * 
 * This sketch was written by SparkFun Electronics, with lots of help from 
 * the Arduino community. This code is completely free for any use.
 * 
 * 15 Dec 2014 B. Huang 
 * 
 * This experiment was inspired by Paul Kassebaum at Mathworks, who made
 * one of the very first non-SparkFun demo projects and brought it to the
 * 2013 Open Hardware Summit in Boston. Thanks Paul!
 ***********************************************************************/

#include <RedBot.h>
RedBotMotors motors;
int leftPower;  // variable for setting the drive power
int rightPower;
int data;  // variable for holding incoming data from PC to Arduino

void setup(void)
{
  Serial.begin(9600);
  Serial.print("Enter in left and right motor power values and click [Send]."); 
  Serial.print("Separate values with a space or non-numeric character.");
  Serial.println();
  Serial.print("Positive values spin the motor CW, and negative values spin the motor CCW.");
}

void loop(void)
{
  // if there is data coming in on the Serial monitor, do something with it.
  if(Serial.available() > 0)
  {
    leftPower = Serial.parseInt();  // read in the next numeric value
    leftPower = constrain(leftPower, -255, 255);  // constrain the data to -255 to +255
    
    rightPower = Serial.parseInt();   // read in the next numeric value
    rightPower = constrain(rightPower, -255, 255);  // constrain the data to -255 to +255

    motors.leftMotor(leftPower);
    motors.rightMotor(rightPower);
    
  }  
}