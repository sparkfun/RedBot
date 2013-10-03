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

// Instantiate the accelerometer. It can only be connected to pins A4
//  and A5, since those are the I2C pins for this board.
RedBotAccel xl;

// Instantiate the encoder. This includes motor control, as well. The 
//  first parameter is the pin that the left wheel encoder is
//  connected to, the second, the right wheel.
RedBotEncoder motor = RedBotEncoder(10, 11);

// Instantiate the sensors. Sensors can only be created for analog input
//  pins; the Xbee software serial uses pins A0 and A1 and the
//  accelerometer uses pins A4 and A5.
RedBotSensor lSen = RedBotSensor(A3);
RedBotSensor cSen = RedBotSensor(A6);
RedBotSensor rSen = RedBotSensor(A7);

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
}

void loop()
{  
  Serial.println(motor.pivot(16, 255));
  delay(2000);
  Serial.println(motor.pivot(16, -255));
  delay(2000);
}
