/***********************************************************************
 * Exp6_2_LineFollowing_IRSensors -- RedBot Experiment 6_2
 *
 * This code reads the three line following sensors on A3, A6, and A7
 * and prints them out to the Serial Monitor. Upload this example to your
 * RedBot and open up the Serial Monitor by clicking the magnifying glass
 * in the upper-right hand corner.
 *
 * This is a real simple example of a line following algorithm. It has 
 * a lot of room for improvement, but works fairly well for a curved track. 
 * It does not handle right angles reliably -- maybe you can come up with a 
 * better solution?
 * 
 * This sketch was written by SparkFun Electronics,with lots of help from
 * the Arduino community. This code is completely free for any use.
 *
 * 18 Feb 2015 B. Huang
 ***********************************************************************/

#include <RedBot.h>
RedBotSensor left = RedBotSensor(A3);   // initialize a left sensor object on A3
RedBotSensor center = RedBotSensor(A6); // initialize a center sensor object on A6
RedBotSensor right = RedBotSensor(A7);  // initialize a right sensor object on A7

// constants that are used in the code. LINETHRESHOLD is the level to detect 
// if the sensor is on the line or not. If the sensor value is greater than this
// the sensor is above a DARK line.
//
// SPEED sets the nominal speed

#define LINETHRESHOLD 800
#define SPEED 60  // sets the nominal speed. Set to any number from 0 - 255.

RedBotMotors motors;
int leftSpeed;   // variable used to store the leftMotor speed
int rightSpeed;  // variable used to store the rightMotor speed

void setup()
{
	Serial.begin(9600);
	Serial.println("Welcome to experiment 6.2 - Line Following");
	Serial.println("------------------------------------------");
	delay(2000);
	Serial.println("IR Sensor Readings: ");
	delay(500);
}

void loop()
{
	Serial.print(left.read());
	Serial.print("\t");  // tab character
	Serial.print(center.read());
	Serial.print("\t");  // tab character
	Serial.print(right.read());
	Serial.println();

	// if on the line drive left and right at the same speed (left is CCW / right is CW)
	if(center.read() > LINETHRESHOLD)
	{
		leftSpeed = -SPEED; 
		rightSpeed = SPEED;
	}
	
	// if the line is under the right sensor, adjust relative speeds to turn to the right
	else if(right.read() > LINETHRESHOLD)
	{
		leftSpeed = -(SPEED + 50);
		rightSpeed = SPEED - 50;
	}

	// if the line is under the left sensor, adjust relative speeds to turn to the left
	else if(left.read() > LINETHRESHOLD)
	{
		leftSpeed = -(SPEED - 50);
		rightSpeed = SPEED + 50;
	}
	
	// if all sensors are on black or up in the air, stop the motors.
	// otherwise, run motors given the control speeds above.
	if((left.read() > LINETHRESHOLD) && (center.read() > LINETHRESHOLD) && (right.read() > LINETHRESHOLD) )
	{
		motors.stop();
	}
	else
	{
		motors.leftMotor(leftSpeed);
		motors.rightMotor(rightSpeed);
		
	}
	delay(0);  // add a delay to decrease sensitivity.
}


