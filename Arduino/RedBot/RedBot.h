#ifndef RedBot_h
#define RedBot_h

#include <Arduino.h>

#define    L_CTRL_1   2
#define    L_CTRL_2   4
#define    PWM_L      5

#define    R_CTRL_1   7
#define    R_CTRL_2   8
#define    PWM_R      6

/**
 * A class for controlling the RedBot's motors.
 * A single object of the RedBotMotor class controls both the left and right motors of the RedBot.
 *
 */
class RedBotMotor
{
  public:
	/**
	 * Create a new object of the RedBotMotor class.
	 *
	 * A single RedBotMotor instance is used for both motors on the RedBot.
	 */
    RedBotMotor();

    /**
     * Run both motors at a given speed.
     *
     * If _speed_ is a positive integer, drives both motors forward, and if
     * _speed_ is a negative integer, drives both motors backward. In either
     * case, the motors are driven at the absolute value at _speed_. Allowable
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
    void drive(int speed);

    /**
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
    void leftDrive(int speed);

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
    void stop();

    /**
     * Discontinue PWM output to the left motor.
     *
     * This method turns off the left motor by stopping PWM output to the motor.
     * After a call to this method, the left motor will continue to coast for a
     * short time. In order to continue driving just the right motor, use
     * RedBotMotor::rightDrive(int speed)
     */
    void leftStop();

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
    void leftBrake();

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
    void rightBrake();

  private:
    void leftFwd(byte speed);
    void leftRev(byte speed);
    void rightFwd(byte speed);
    void rightRev(byte speed);
};

/**
 * A class for controlling the RedBot's sensors.
 *
 * A single object of the class RedBotSensor is needed for each sensor that you want to use on the RedBot.
 *
 */
class RedBotSensor
{
  public:
	/**
	 * Create a new object of the RedBotSensor class.
	 *
	 * _pin_ is the analog input pin that the sensor is connected to.
	 *
	 * Usage Example:
	 *
	 * #include <RedBot.h>
	 *
	 * RedBotSensor sensor = RedBotSensor (A2);
	 */
    RedBotSensor(int pin);

    /**
     * Read the analog level of the sensor.
     *
     * This method is primarily used when you want to do your own data
     * processing instead of relying on the library's edge detection. 
     */
    int read();

    /**
     * Determines if the current sensor reading is within the configured levels.
     *
     * This method returns _true_ if the sensor's current analog value is
     * within the configured levels. If the sensor's current analog value is
     * outside the configured levels, RedBotSensor::check() returns _false_.
     */
    boolean check();

    /**
     * Set the background/default sensor reading level.
     *
     * Calling this method sets the sensor's reading level that corresponds to
     * an uninteresting sensor reading. For example, if you are trying to follow
     * a black line on a white background, you would call
     * RedBotSensor::setBPLevel() when the light sensor is over the white
     * background.
     */
    int setBGLevel();

    /**
     * Set the forground/active sensor reading level.
     *
     * Calling this method sets the sensor's reading level that corresponds to
     * an interesting sensor reading. For example, if you are trying to follow
     * a black line on a white background, you would call
     * RedBotSensor::setDetectLevel() when the light sensor is over the black
     * background.
     */
    int setDetectLevel();

  private:
    int _pin;
    int _BGLevel;
    int _BGSD;
    int _detectLevel;
    int _detectSD;
};

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
	/**
	 * Creates an object of the class RedBotAccel
	 */
    RedBotAccel();

    /**
     * Copy the current accelerometer values into the class's attributes.
     *
     * In order to "read" the accelerometer's current state, you must first call
     * RedBotAccel::read() to set RedBotAccel::x, RedBotAccel::y, and
     * RedBotAccel::z which you can then read and do your own processing.
     */
    void read();

    /**
     * Enable bump detection.
     *
     * A "bump" is an acceleration event that occurs along the X-axis. After
     * enabling bump detection, use to RedBotAccel::checkBump() to do the actual
     * detection.
     */
    void enableBump();

    /**
     * Check to see if a "bump" event has occurred.
     *
     * This method returns _true_ if a "bump" event has occurred since the last
     * time that RedBotAccel::checkBump() has been called. Before using
     * RedBotAccel::checkBump(), bump detection must be enabled via
     * RedBotAccel::enableBump(). Note that a "bump" is an acceleration event
     * that occurs along the X-axis.
     */
    boolean checkBump();

    /**
     * Set the threshold for what is considered a "bump" event.
     *
     * If the default "bump" event threshold is too strong or too weak for your
     * application/sketch, you can provide a value of 0-127 inclusive to use as
     * the new threshold. Prior to calling RedBotAccel::setBumpThresh(int xTresh)
     * "bump" detection must first be enabled via RedBotAccel::enableBump().
     */
    void setBumpThresh(int xThresh);

    /**
     * Read the last copied X-axis reading.
     *
     * This class member is set by calling RedBotAccel::read() and can be used
     * to do your own data processing.
     */
    int x;

    /**
     * Read the last copied Y-axis reading.
     *
     * This class member is set by calling RedBotAccel::read() and can be used
     * to do your own data processing.
     */
    int y;

    /**
     * Read the last copied Z-axis reading.
     *
     * This class member is set by calling RedBotAccel::read() and can be used
     * to do your own data processing.
     */
    int z;

  private:
    void xlWriteBytes(byte addr, byte *buffer, byte len);
    void xlReadBytes(byte addr, byte *buffer, byte len);
};

#endif RedBot_h
