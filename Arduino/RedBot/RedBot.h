/****************************************************************
Core header file for all the various RedBot functions.

There is additional license info below regarding the use of the
SoftwareSerial library from Arduino 1.0.5; I had good and sound
reasons for creating a derivative class rather than asking users
to simply use the existing library, which are documented below.

This code is beerware; if you use it, please buy me (or any other
SparkFun employee) a cold beverage next time you run into one of
us at the local.

21 Jan 2014- Mike Hord, SparkFun Electronics

Code developed in Arduino 1.0.5, on an SparkFun Redbot v12.
****************************************************************/

#ifndef RedBot_h
#define RedBot_h

#include <Arduino.h>

// Pin aliases for the motor controller.
#define    L_CTRL_1   2
#define    L_CTRL_2   4
#define    PWM_L      5

#define    R_CTRL_1   7
#define    R_CTRL_2   8
#define    PWM_R      6

// PCINT functionality aliases. Each PCINT has a value set up when the
//  class member gets created, and the PCINT service routine will handle
//  the choosing the appropriate response to the interrupt.

#define NOT_IN_USE    0
#define WHISKER       1
#define LENCODER      2
#define RENCODER      3
#define SW_SERIAL     4

#define PCINT_A0      0
#define PCINT_A1      1
#define PCINT_A2      2
#define PCINT_A3      3
#define PCINT_A4      4
#define PCINT_A5      5
#define PCINT_3       6
#define PCINT_9       7
#define PCINT_10      8
#define PCINT_11      9

enum WHEEL {LEFT, RIGHT, BOTH}; // Variable for which wheel you're interested in
                  //  when you do things in the encoder class.

// These three functions need to work from within multiple classes, so we keep
//  them separate and add them as friend functions where appropriate.
void setPinChangeInterrupt(int pin, byte role); // The "role" of each pin is
                  //  stored in an array which is accessed in the interrupt
                  //  handler to determine what should be done on a falling edge
                  //  PC interrupt.
void pinFunctionHandler(byte pinIndex); // This is the function which actually
                  //  handles the legwork after the interrupt has identified
                  //  which pin caught the interrupt.
void brake(void); // Globally accessible motor brake. I couldn't figure out how
                  //  to set a function pointer to the RedBotMotor class
                  //  function, and it's a small function, so I just made a
                  //  global in the library.
void PC0Handler(byte PBTemp);
void PC1Handler(byte PCTemp);
void PC2Handler(byte PDTemp);


// This class handles motor functionality. I expect one instance of this at the
//  start of a piece of RedBot code.
class RedBotMotor
{
  public:
    RedBotMotor();          // Constructor. Mainly sets up pins.
    void drive(int speed);  // Drive in direction given by sign, at speed given
                            //  by magnitude of the parameter.
    void pivot(int speed);  // Pivot more or less in place. Turns motors in
                            //  opposite directions. Positive values correspond
                            //  to anti-clockwise rotation.
    void rightDrive(int speed); // Drive just the left motor, as drive().
    void leftDrive(int speed);  // Drive just the right motor, as drive().
    void stop();            // Stop motors, but allow them to coast to a halt.
    void brake();           // Quick-stop the motors, shorting the leads.
    void rightStop();       // Stop right motor, as with stop().
    void leftStop();        // Stop left motor, as with stop().
    void leftBrake();       // Quick-stop left motor, as with brake().
    void rightBrake();      // Quick-stop right motor, as with brake().
     * and 0 to 75 inclusive may not provide enough torque to start the motor
     * turning.
     *
     * Usage Example:
     *
     * #include <RedBot.h>
     *
     * RedBotMotor motor;
     *
     * void setup() {
     *
     * }
     *
     * void loop () {
     *
     *   // Drive forward at a speed of 200
     *
     *   motor.drive (200);
     *
     *   // Drive backward at a speed of 150
     *
     *   motor.drive (-150)
     *
     * }
     *
     */
     * Run the left motor at a given speed.
     *
     * If _speed_ is a positive integer, drives the motor forward, and if
     * _speed_ is a negative integer, drives motor backward. In either
     * case, the motor is driven at the absolute value at _speed_. Allowable
     * values for _speed_ are -255 to 255 inclusive, however values in -75 to 0
     * and 0 to 75 inclusive may not provide enough torque to start the motor
     * turning.
     *
     * Usage Example:
     *
     * #include <RedBot.h>
     *
     * RedBotMotor motor;
     *
     * void setup() {
     *
     * }
     *
     * void loop () {
     *
     *   // Drive the left motor forward at a speed of 200
     *
     *   motor.LeftDrive (200);
     *
     *   // Drive the left motor backward at a speed of 150
     *
     *   motor.leftDrive (-150)
     *
     * }
     */

    /**
     * Run the right motor at a given speed.
     *
     * If _speed_ is a positive integer, drives the motor forward, and if
     * _speed_ is a negative integer, drives motor backward. In either
     * case, the motor is driven at the absolute value at _speed_. Allowable
     * values for _speed_ are -255 to 255 inclusive, however values in -75 to 0
     * and 0 to 75 inclusive may not provide enough torque to start the motor
     * turning.
     *
     * Usage Example:
     *
     * #include <RedBot.h>
     *
     * RedBotMotor motor;
     *
     * void setup() {
     *
     * }
     *
     * void loop () {
     *
     *   // Drive the right motor forward at a speed of 200
     *
     *   motor.RightDrive (200);
     *
     *   // Drive the right motor backward at a speed of 150
     *
     *   motor.rightDrive (-150)
     *
     * }
     */
    void rightDrive(int speed);

    /**
     * Pivot the RedBot to either the left or right.
     *
     * If _speed_ is a positive integer, the RedBot pivots to the left. If
     * _speed_ is a negative integer, the RedBot pivots to the right. In
     * either case, the motors are driven in their respective directions at
     * the absolute value of _speed_. When pivoting left, the left motor drives
     * backwards and the right motor drives forward; when pivoting right, the
     * motors drive in the opposite directions. Allowable values for _speed_
     * are -255 to 255 inclusive, however values in -75 to 0 and 0 to 75
     * inclusive may not provide enough torque to start the motor turning.
     *
     * Usage Example:
     *
     * #include <RedBot.h>
     *
     * RedBotMotor motor;
     *
     * void setup() {
     *
     * }
     *
     * void loop() {
     *
     *   // Pivot to the left at a speed of 150
     *
     *   motor.pivot (150);
     *
     *   // Pivot to the right at a speed of 75
     *
     *   motor.pivot (-75);
     *
     * }
     */
    void pivot(int speed);

    /**
     * Discontinue PWM output to both motors.
     *
     * This method turns off both motors by stopping PWM output to the motors.
     * After a call to this method, the motors will continue to coast for a
     * short time.
     *
     * Usage Example:
     *
     * #include <RedBot.h>
     *
     * RedBotMotor motor;
     *
     * void setup() {
     *
     * }
     *
     * void loop() {
     *
     * // Drive for a bit
     *
     * for (int x = 0; x < 1000; x++) {
     *
     *    motor.drive (200);
     *
     * }
     *
     * // Stop the motors
     *
     * motor.stop();
     *
     * }
     */
     * Discontinue PWM output to the left motor.
     *
     * This method turns off the left motor by stopping PWM output to the motor.
     * After a call to this method, the left motor will continue to coast for a
     * short time. In order to continue driving just the right motor, use
     * RedBotMotor::rightDrive(int speed)
     */

    /**
     * Discontinue PWM output to the right motor.
     *
     * This method turns off the right motor by stopping PWM output to the motor.
     * After a call to this method, the right motor will continue to coast for a
     * short time. In order to continue driving just the left motor, use
     * RedBotMotor::leftDrive(int speed)
     */
    void rightStop();

    /**
     * Immediately stop both motors and hold their current positions.
     *
     * The RedBotMotor::brake() method effectively shorts the terminals of the
     * motors and therefore results in the motors stopping much more quickly
     * than the RedBotMotor::stop() method. After a call to
     * RedBotMotor::brake(), the motors will be much harder to turn, which will
     * allow the RedBot to hold its position on a slope.
     *
     * Usage Example:
     *
     * #include <RedBot.h>
     *
     * RedBotMotor motor;
     *
     * void setup() {
     *
     * }
     *
     * void loop() {
     *
     * // Drive for a bit
     *
     * for (int x = 0; x < 1000; x++) {
     *
     *    motor.drive (200);
     *
     * }
     *
     * // Stop the motors and hold current position
     *
     * motor.brake();
     *
     * }
     */
    void brake();

    /**
     * Immediately stop the left motor and hold its current position.
     *
     * The RedBotMotor::leftBrake() method effectively shorts the terminals of     * the left motor and therefore results in the motor stopping much more
     * quickly than the RedBotMotor::leftRtop() method. After a call to
     * RedBotMotor::leftBrake(), the motor will be much harder to turn, which
     * will allow the RedBot to hold its position on a slope. The right motor
     * will still be able to be driven via RedBotMotor::rightDrive() method.
     */

    /**
     * Immediately stop the right motor and hold its current position.
     *
     * The RedBotMotor::rightBrake() method effectively shorts the terminals of
     * the right motor and therefore results in the motor stopping much more
     * quickly than the RedBotMotor::rightRtop() method. After a call to
     * RedBotMotor::rightBrake(), the motor will be much harder to turn, which
     * will allow the RedBot to hold its position on a slope. The left motor
     * will still be able to be driven via RedBotMotor::leftDrive() method.
     */

  private:
    void leftFwd(byte speed); // These functions are pretty self-explanatory,
    void leftRev(byte speed); //  and are called by the above functions once
    void rightFwd(byte speed);//  sign has been used to determine direction.
    void rightRev(byte speed);
};

// Handler for encoder sensors. Assume only one of this class is present.
//  When a negative going edge happens on an encoder pin, a counter is
//  incremented (or decremented), depending on the direction last determined
//  by one of the motor direction commands.
class RedBotEncoder
{
  // We declare a couple of friends, so they can have access to the private
  //  members of this class.
  friend class RedBotMotor;  // Needs access to lDir and rDir.
  friend void pinFunctionHandler(byte pinIndex); // Called from within the
                             //  ISRs, this function increments the counts
                             //  by calling wheelTick().
  public:
    RedBotEncoder(int lPin, int rPin); // Constructor. Assigns pins, pin
                             //  functions, zeroes counters, and adds a
                             //  reference to the new encoder object for other
                             //  library members to access.
    void clearEnc(WHEEL wheel); // Zaps the encoder count for a given wheel (or
                             //  for both wheels).
    long getTicks(WHEEL wheel); // Returns the encoder count for a wheel.
  private:
    void wheelTick(WHEEL wheel); // Increment or decrement a wheel's counts,
                             //  depending on which way the motor is turning.
    long lCounts;            // Holds the number of ticks for that wheel's
    long rCounts;            //  encoder.
    char lDir;               // Direction is set by the motor class, according
    char rDir;               //  to what the most recent motion direction for
                             //  the given wheel was.
};

// This is the reflectance sensor used for eg line following and table edge
//  detection. It's pretty crude, but since they're analog sensors, they're
//  kind of hard to work with.
class RedBotSensor
{
  public:
    RedBotSensor(int pin);  // Configure a pin as a sensor.
    int read();             // Return the current value of the pin.
    boolean check();        // In theory, this will be true if a deviation from
                            //  detectLevel is found; false otherwise.
    int setBGLevel();       // You can calibrate the sensor to detect a deviation
    int setDetectLevel();   //  from detectLevel; these functions allow for that.
    boolean calStatus();    // Have both calibrated levels been set yet?
	 * #include <RedBot.h>
	 *
	 * RedBotSensor sensor = RedBotSensor (A2);
	 */

    /**
     * Read the analog level of the sensor.
     *
     * This method is primarily used when you want to do your own data
     * processing instead of relying on the library's edge detection. 
     */

    /**
     * Determines if the current sensor reading is within the configured levels.
     *
     * This method returns _true_ if the sensor's current analog value is
     * within the configured levels. If the sensor's current analog value is
     * outside the configured levels, RedBotSensor::check() returns _false_.
     */

    /**
     * Set the background/default sensor reading level.
     *
     * Calling this method sets the sensor's reading level that corresponds to
     * an uninteresting sensor reading. For example, if you are trying to follow
     * a black line on a white background, you would call
     * RedBotSensor::setBPLevel() when the light sensor is over the white
     * background.
     */

    /**
     * Set the forground/active sensor reading level.
     *
     * Calling this method sets the sensor's reading level that corresponds to
     * an interesting sensor reading. For example, if you are trying to follow
     * a black line on a white background, you would call
     * RedBotSensor::setDetectLevel() when the light sensor is over the black
     * background.
     */

  private:
    int _pin;
    int _BGLevel;
    int _detectLevel;
};

// This handles the physical wire-whisker type bumper.
class RedBotBumper
{
  public:
    RedBotBumper(int pin); // Simple constructor; when the bumper gets hit, the
                           //  motors will stop.
    RedBotBumper(int pin, void(*functionPointer)(void)); // If the user wishes
                           //  to do something other than stop on a whisker,
                           //  bump, they can write a function to do so, and
                           //  use this constructor.
  private:
    void setBumpFunction(int pin, void(*functionPointer)(void));
};

// We have a bunch of stuff associated with the accelerometer here. We're going
//  to implement our own I2C functions, too, to make things easy on ourselves.
#define XL_ADDR     0x1D // I2C address of the MMA8452Q accelerometer
#define I2C_READ    0x01 // I2C read bit set
// Some values we'll load into TWCR a lot
#define START_COND  0xA4 // (1<<TWINT) | (1<<TWSTA) | (1<<TWEN)
#define STOP_COND   0x94 // (1<<TWINT) | (1<<TWSTO) | (1<<TWEN)
#define CLEAR_TWINT 0x84 // (1<<TWINT) | (1<<TWEN)
#define NEXT_BYTE   0xC4 // (1<<TWINT) | (1<<TWEA) | (1<<TWEN)

/**
 * A class for controlling the RedBot's accelerometer.
 *
 * Since the RedBot's accelerometer uses the I2C protocol, and is only
 * connected to A4 and A5 on the RedBot, there should only ever be a single
 * object of this class instantiated in your application/sketch.
 */
class RedBotAccel
{
  public:
    RedBotAccel();     // Constructor...doesn't do much, since we re-configure
                       //  the TWI registers on each send/receive.
    void read();       // Puts the current readings of the accelerometer into
                       //  the x, y, and z variables to be checked by user.
    void enableBump(); // Put the accelerometer into a bump detection mode.
                       //  Useful for tap-input to the robot.
    boolean checkBump(); // Check to see if a tap has occurreed since the last
                       //  time this function was called.
    void setBumpThresh(int xThresh); // Adjust the threshold at which a bump
                       //  is detected. Too low and motion will set it off, too
                       //  high and it won't trigger when you want it to.
    int x;             // Rather than forcing users to grok pointers to read
    int y;             //  the three axes, we just populate this variables and
    int z;             //  let them be read as normal variables.
    /**
     * Enable bump detection.
     *
     * A "bump" is an acceleration event that occurs along the X-axis. After
     * enabling bump detection, use to RedBotAccel::checkBump() to do the actual
     * detection.
     */

    /**
     * Check to see if a "bump" event has occurred.
     *
     * This method returns _true_ if a "bump" event has occurred since the last
     * time that RedBotAccel::checkBump() has been called. Before using
     * RedBotAccel::checkBump(), bump detection must be enabled via
     * RedBotAccel::enableBump(). Note that a "bump" is an acceleration event
     * that occurs along the X-axis.
     */

    /**
     * Set the threshold for what is considered a "bump" event.
     *
     * If the default "bump" event threshold is too strong or too weak for your
     * application/sketch, you can provide a value of 0-127 inclusive to use as
     * the new threshold. Prior to calling RedBotAccel::setBumpThresh(int xTresh)
     * "bump" detection must first be enabled via RedBotAccel::enableBump().
     */

    /**
     * Read the last copied X-axis reading.
     *
     * This class member is set by calling RedBotAccel::read() and can be used
     * to do your own data processing.
     */

    /**
     * Read the last copied Y-axis reading.
     *
     * This class member is set by calling RedBotAccel::read() and can be used
     * to do your own data processing.
     */

    /**
     * Read the last copied Z-axis reading.
     *
     * This class member is set by calling RedBotAccel::read() and can be used
     * to do your own data processing.
     */

  private:
    void xlWriteBytes(byte addr, byte *buffer, byte len); // addr is the 
                       //  memory location on the device to be written to; buffer
                       //  and len are fairly self explanatory. Note that the
                       //  address in the device auto-increments after each
                       //  written, allowing consecutive registers to be written
                       //  with only one command.
    void xlReadBytes(byte addr, byte *buffer, byte len); // The same as the
                       //  write command, but with reading. Same rules apply.
};

// This is lifted from the SoftwareSerial version that shipped with Arduino
//  v1.0.5. I needed to rework that rather than use the existing SoftwareSerial
//  library because I need to share the pin change ISRs with other classes in
//  this library. Also, because I'm constraining the environment, I can make
//  some optimizations to the code. I'm leaving in the full history, for
//  citation's sake. People should know I didn't do all this.

/*
SoftwareSerial.h (formerly NewSoftSerial.h) - 
Multi-instance software serial library for Arduino/Wiring
-- Interrupt-driven receive and other improvements by ladyada
   (http://ladyada.net)
-- Tuning, circular buffer, derivation from class Print/Stream,
   multi-instance support, porting to 8MHz processors,
   various optimizations, PROGMEM delay tables, inverse logic and 
   direct port writing by Mikal Hart (http://www.arduiniana.org)
-- Pin change interrupt macros by Paul Stoffregen (http://www.pjrc.com)
-- 20MHz processor support by Garrett Mace (http://www.macetech.com)
-- ATmega1280/2560 support by Brett Hagman (http://www.roguerobotics.com/)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

The latest version of this library can always be found at
http://arduiniana.org.
*/

#include <inttypes.h>
#include <Stream.h>

/******************************************************************************
* Definitions
******************************************************************************/

#define _SS_MAX_RX_BUFF 64 // RX buffer size
#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

class RedBotSoftwareSerial : public Stream
{
  friend void pinFunctionHandler(byte pinIndex);
  
  public:
    // public methods
    RedBotSoftwareSerial();
    ~RedBotSoftwareSerial();
    void begin(long speed);
    void end();
    bool overflow() { bool ret = _buffer_overflow; _buffer_overflow = false; return ret; }
    int peek();

    virtual size_t write(uint8_t byte);
    virtual int read();
    virtual int available();
    virtual void flush();
    
    using Print::write;
    
  private:
    // per object data
    uint8_t _receivePin;
    uint8_t _receiveBitMask;
    volatile uint8_t *_receivePortRegister;
    uint8_t _transmitBitMask;
    volatile uint8_t *_transmitPortRegister;

    uint16_t _rx_delay_centering;
    uint16_t _rx_delay_intrabit;
    uint16_t _rx_delay_stopbit;
    uint16_t _tx_delay;

    uint16_t _buffer_overflow:1;

    // static data
    static char _receive_buffer[_SS_MAX_RX_BUFF]; 
    static volatile uint8_t _receive_buffer_tail;
    static volatile uint8_t _receive_buffer_head;
    static RedBotSoftwareSerial *active_object;

    // private methods
    void recv();
    uint8_t rx_pin_read();
    void tx_pin_write(uint8_t pin_state);
    void setTX(uint8_t transmitPin);
    void setRX(uint8_t receivePin);

    // private static method for timing
    static inline void tunedDelay(uint16_t delay);

};

// We're going to create a special class now, to interface with the onboard
//  XBee header. Since we've got the option of either software or hardware serial,
//  I'm going to allow the user to choose between modes.

class RedBotRadio
{
  public:
    RedBotRadio();      // Constructor.
  private:
  
};

#endif