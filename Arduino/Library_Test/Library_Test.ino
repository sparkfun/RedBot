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
// Include the library.
#include <RedBot.h>
#include <Servo.h>
#include "notes.h"

// Instantiate the motors.
RedBotMotor motors;

// Instantiate the accelerometer. It can only be connected to pins A4
//  and A5, since those are the I2C pins for this board.
RedBotAccel xl;

// Instantiate our encoder. 
RedBotEncoder encoder = RedBotEncoder(A2, A3);

// Instantiate the sensors. Sensors can only be created for analog input
//  pins; the accelerometer uses pins A4 and A5. Also, since A6 and A7
//  can *only* be used as analog inputs, that's a good place for these.
RedBotSensor lSen = RedBotSensor(A6);
RedBotSensor rSen = RedBotSensor(A7);

// Instantiate a couple of whisker switches.
RedBotBumper lBumper(10, &bump);
RedBotBumper rBumper(11, &bump);

// Instantiate a software serial port
RedBotSoftwareSerial swsp;

// Instantiate a servo- this is outside of the RedBot library!
Servo servo;

// Create an alias for our beeper pin, for ease of use.
#define BEEPER 9

// Create an alias for the onboard pushbutton.
#define BUTTON_PIN 12

// Create an alias for the onboard LED.
#define LED_PIN 13

// Constants for the levels that determine detection of the line.
const int bgLevel = 150;
const int lineLevel = 700;

// Flag for bumpers to send the signal that something's wrong and the motors should
//  be disabled for now. Set in the bump functions, volatile so the change is sure
//  to propagate to the loop() function.
volatile boolean bumped = true;

void setup()
{
  Serial.begin(57600);
  Serial.println("Hello world!");
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  horn();
  swsp.begin(9600);
  swsp.print("Hello, world");
  servo.attach(3);
}


void loop()
{
  static unsigned long loopStart = millis();
  const unsigned long loopDelay = 150;
  static int angle = 0;
  static int angleDelta = 5;
  
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    bumped = false;
  }
  
  if (loopStart + 250 < millis())
  {
    loopStart = millis();
    servo.write(angle);
    if (angle + angleDelta > 120) angleDelta *= -1;
    if (angle + angleDelta < 0 ) angleDelta *= -1;
    angle += angleDelta;
  }
  
  // All this line-follow-y stuff should only be invoked when we're clear to move;
  //  if one of the bump sensors was set off, we should stay still until the user
  //  intervenes for us.
  if (!bumped)
  {
    // Line following code: turn away from any sensor that is above the line
    //  threshold.
    // Case 1: both white. Drive forward!
    if (lSen.read() < bgLevel && rSen.read() < bgLevel) motors.drive(100);
    // Case 2: right sensor is on black. Must recenter.
    if (rSen.read() > lineLevel) 
    {
      motors.rightDrive(-180);
      motors.leftBrake();
    }
    // Case 3: left sensor is on black. Must recenter.
    if (lSen.read() > lineLevel) 
    {
      motors.leftDrive(-180);
      motors.rightBrake();
    }
    // Case 4: both sensors see dark
    if (lSen.read() > lineLevel && rSen.read() >lineLevel)
    {
      motors.leftDrive(-180);
      motors.rightDrive(-180);
    }
  }
  else motors.brake();
}

void bump()
{
  motors.brake();
  bumped = true;
  tone(BEEPER, 150, 750);
}

const int SN = 100;
const int EN = 200;
void horn()
{
  tone(BEEPER, noteG5, SN);
  delay(SN);
  tone(BEEPER, noteE5, SN);
  delay(SN);
  tone(BEEPER, noteC5, EN);
  delay(EN);
  tone(BEEPER, noteC5, EN);
  delay(EN);
  tone(BEEPER, noteC5, SN);
  delay(SN);
  tone(BEEPER, noteD5, SN);
  delay(SN);
  tone(BEEPER, noteE5, SN);
  delay(SN);
  tone(BEEPER, noteF5, SN);
  delay(SN);
  tone(BEEPER, noteG5, EN);
  delay(EN);
  tone(BEEPER, noteG5, EN);
  delay(EN);
  tone(BEEPER, noteG5, EN);
  delay(EN);
  tone(BEEPER, noteE5, EN);
  delay(EN);
}
