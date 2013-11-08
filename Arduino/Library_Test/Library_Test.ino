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
RedBotBumper lBumper(10);
RedBotBumper rBumper(11);

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

void setup()
{
  Serial.begin(57600);
  Serial.println("Hello world!");
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  tone(BEEPER, 1000, 250);
  delay(250);
  tone(BEEPER, 1500, 250);
  delay(250);
  tone(BEEPER, 2000, 250);
  delay(250);
  swsp.begin(9600);
  swsp.print("Hello, world");
  servo.attach(3);
}


void loop()
{
  static unsigned long loopStart = millis();
  const unsigned long loopDelay = 250;
  static int angle = 0;
  static int angleDelta = 5;
  
  
  
  if (loopStart + loopDelay < millis())
  {
    loopStart = millis();
    servo.write(angle);
    if (angle + angleDelta > 120) angleDelta *= -1;
    if (angle + angleDelta < 0 ) angleDelta *= -1;
    angle += angleDelta;
  }
}
