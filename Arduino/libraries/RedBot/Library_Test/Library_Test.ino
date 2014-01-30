/***********************************************************************
RedBot Library_Test

Created 30 Jul 2013 by Mike Hord @ SparkFun Electronics.

This code is beerware- feel free to make use of it, with or without
attribution, in your own projects. If you find it helpful, buy me a beer
the next time you see me at the local- or better yet, shop SparkFun!

Full-featured library demo for the RedBot library and its attendant
sensors and inputs.

The code plays a tone on startup, or when a whisker bumps something.
Whisker bumps also stop the motion. The 'bot waits for an input on the
onboard pushbutton, then drives forward, attempting to follow a line on
the surface. After the right wheel has traveled 75 ticks (about 6
revolutions, although that can vary depending on what it does while
tracking the line), it stops.

If the accelerometer detects a sizable change in inclination while the
'bot is in motion, you get a surprise!

There's also a provision for sending serial data back via an XBee; at
the moment, it just reports the distance according to the right wheel
encoder.

Finally, it scans a small servo motor attached to pin 3 back and forth,
slowly. I put a tiny monster finger puppet on mine.

The included "notes.h" file has frequencies for a piano keyboard's
worth of notes, for your music-playing enjoyment.
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
RedBotEncoder encoder = RedBotEncoder(A2, A3); // left, right

// Instantiate the sensors. Sensors can only be created for analog input
//  pins; the accelerometer uses pins A4 and A5. Also, since A6 and A7
//  can *only* be used as analog inputs, that's a good place for these.
RedBotSensor lSen = RedBotSensor(A6);
RedBotSensor rSen = RedBotSensor(A7);

// Instantiate a couple of whisker switches. Call bump() when one of them
//  hits something. There's no stopping you having a different function for
//  each whisker; I just chose not to.
RedBotBumper lBumper(10, &bump);
RedBotBumper rBumper(11, &bump);

// Instantiate a software serial port. Note that the regular Arduino
//  SoftwareSerial won't work! It steals resources that the sensor
//  inputs on the RedBot need. Also note that the RedBot version has
//  no input options- it automatically connects to the pins used for
//  the onboard XBee header.
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
const int bgLevel = 600;
const int lineLevel = 700;

// Flag for bumpers to send the signal that something's wrong and the motors should
//  be disabled for now. Set in the bump functions, volatile so the change is sure
//  to propagate to the loop() function.
volatile boolean bumped = true;

void setup()
{
  // We *probably* won't see the hardware serial data; what good is a robot
  //  that has to be tethered to a computer?
  Serial.begin(57600);
  Serial.println("Hello world!");
  // Set up our two built-in IO devices- the button and the LED.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  // Play a tone for audible reset detection.
  tone(BEEPER, 2600, 750);
  delay(750);
  // Send out a hello via the XBee, if one is present.
  swsp.begin(9600);
  swsp.print("Hello, world");
  servo.attach(3);
}

void loop()
{
  // These static variables will be initialized once, then remain valid
  //  through each iteration of the loop.
  
  // Two loop timers; we have one loop that happens four times a second
  //  and one that happens ten times a second.
  static unsigned long loopStart = millis();
  static unsigned long loopStart2 = millis();
  // We're doing a crude low-pass filter on the accelerometer; we want
  //  two consecutive high values so we don't trigger our surprise on
  //  transient events, only on a significant change in angle.
  static int lastXAccel = xl.x;
  // These two variables handle the current position and position
  //  change of the scanning servo motor.
  static int angle = 0;
  static int angleDelta = 5;
  
  // Wait for the button to be pressed, then turn off the "bumped" flag
  //  so the motors can run. Also, clear the encoders, so we can track
  //  our motion.
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    bumped = false;
    encoder.clearEnc(BOTH);
  }
  // Dump the current distance count on the right wheel to the serial
  //  port, just for something to do.
  swsp.println(encoder.getTicks(RIGHT));
  // If we pass 75 ticks on the right wheel, treat that the same as we
  //  would a bumper hit and stop moving.
  if (encoder.getTicks(RIGHT) > 75) bumped = true;
  
  // This is our ten-times-a-second loop. It's watching the accelerometer
  //  and, when the 'bot senses an incline, setting off our surprise.
  if (loopStart2 + 100 < millis())
  {
    loopStart2 = millis();
    lastXAccel = xl.x;
    xl.read();
    if (!bumped)
    {
      if (xl.x > 6000 && lastXAccel > 6000)
      {
        motors.brake();
        horn();
        motors.drive(255);
        delay(5000);
        motors.brake();
        bumped = true; 
      }
    }
  }
  
  // This is the four-times-a-second loop. It scans a servo from left to
  //  right and back again.
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
      motors.rightDrive(-100);
      motors.leftBrake();
    }
    // Case 3: left sensor is on black. Must recenter.
    if (lSen.read() > lineLevel) 
    {
      motors.leftDrive(-100);
      motors.rightBrake();
    }
    // Case 4: both sensors see dark
    if (lSen.read() > lineLevel && rSen.read() >lineLevel)
    {
      motors.leftDrive(-100);
      motors.rightDrive(-100);
    }
  }
  else motors.brake();
}

// This is the function that gets called when we bump something. It
//  stops the motors, signals that a bump occurred (so loop() doesn't
//  just start the motors back up), and issues a nasty little tone to
//  tell the user what's up.
void bump()
{
  motors.brake();
  bumped = true;
  tone(BEEPER, 150, 750);
}

// This is all for our surprise. SN is the length of a sixteenth note,
//  in milliseconds, and EN is the length of an eighth note.
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
