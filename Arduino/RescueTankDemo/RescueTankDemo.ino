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
// Include the libraries. We make a provision for using the Xbee header
//  via software serial to report values, but that's not really used in
//  the code anywhere.
#include <RedBot.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// Instantiate the motor control class. This only needs to be done once
//  and indeed SHOULD only be done once!
RedBotMotor motor;

Servo climber;

// Create a software serial connection. See the Arduino documentation
//  for more information about this. The pins used here are the hard
//  wired pins the Xbee header connects to.
SoftwareSerial xbee(15, 14);

void setup()
{
  Serial.begin(57600);
  xbee.begin(57600);
  Serial.println("Hello world!");
  xbee.println("Hello world!");
  
  climber.attach(3);
  climber.writeMicroseconds(1200);
  
  pinMode(10, INPUT);
  pinMode(11, INPUT);
}

void loop()
{ 
  motor.drive(150);
  if ((digitalRead(10) == LOW) || (digitalRead(11) == LOW) )
  {
    motor.brake();
    climber.writeMicroseconds(2500);
    delay(500);
    motor.drive(150);
    delay(1000);
    motor.brake();
    climber.writeMicroseconds(1200);
  }
}
