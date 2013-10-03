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

enum PIN_ROLE {NOT_IN_USE, WHISKER, LENCODER, RENCODER, SW_SERIAL};

enum PCINT_INDEX {PCINT_A0, PCINT_A1, PCINT_A2, PCINT_A3, PCINT_A4, 
                  PCINT_A5, PCINT_3, PCINT_9, PCINT_10, PCINT_11};

enum WHEEL {LEFT, RIGHT, BOTH}; // Variable for which wheel you're interested in
                  //  when you do things in the encoder class.

// These three functions need to work from within multiple classes, so we keep
//  them separate and add them as friend functions where appropriate.
void setPinChangeInterrupt(int pin, PIN_ROLE role); // The "role" of each pin is
                  //  stored in an array which is accessed in the interrupt
                  //  handler to determine what should be done on a falling edge
                  //  PC interrupt.
void pinFunctionHandler(PCINT_INDEX pinIndex); // This is the function which actually
                  //  handles the legwork after the interrupt has identified
                  //  which pin caught the interrupt.
void brake(void); // Globally accessible motor brake. I couldn't figure out how
                  //  to set a function pointer to the RedBotMotor class
                  //  function, and it's a small function, so I just made a
                  //  global in the library.

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
  friend void pinFunctionHandler(PCINT_INDEX pinIndex); // Called from within the
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

#endif RedBot_h
