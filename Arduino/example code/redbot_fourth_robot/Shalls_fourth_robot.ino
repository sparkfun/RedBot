/***********************************************************************
RedBot test code

Created 30 Jul 2013 by Jeff @ SparkFun Electronics.

This code is beerware- feel free to make use of it, with or without
attribution, in your own projects. If you find it helpful, buy me a beer
the next time you see me at the local- or better yet, shop SparkFun!

***********************************************************************/
//include the redbot library to get the functions out of the library
#include <RedBot.h>




// Instantiate the motor control class. This only needs to be done once
//  and indeed SHOULD only be done once!
RedBotMotor motor;

int motorSpeed=80;//We declare a variable(it's just a place to store a number), we'll use it to control the motor speed
int change = 5;// we use this varible to adjust how much the speed changes
void setup()
{
  Serial.begin(9600);//This will open the serial port to send values out to calibrate sensors
  
  Serial.println("Hello world!");//This should print once to make sure you're getting serial communication
 
}

void loop()
{  

  
    motor.drive(motorSpeed);   // we use the varible to adjust the motorspeed
    
    motorSpeed= motorSpeed+ change;//everytime through the loop we add"change", or 10 as it's written in the code above.
    
    if(motorSpeed<=80||motorSpeed>=254)
    {
     change = change*-1; 
    }
    Serial.println(motorSpeed);
    delay(100); //we put in a pause so we can see the change happen, without it, it happens so fast we see no change(try taking it out).
  
}
