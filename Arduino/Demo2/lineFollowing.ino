// Speed levels for looking for line and following once it's found. Go
//  too fast and you're liable to lose the line.
#define seekSpd    150
#define fwdSpd     200

void followCal()
{
  static boolean centerOnLine = false;
  static boolean onLine = false;
  
  // Okay, logic time! We're going to try and keep the center sensor on
  //  the line.
  
  // Start with the "no line detected" case: drive forward, slowly, until
  //  we see a line on the center sensor.
  if (!cSen.check() && 
      centerOnLine == false) motor.drive(seekSpd);
  
  if (cSen.check()) centerOnLine = true;
  
  // Okay, now we've found a line. Let's swivel to the right until our
  //  right sensor locks onto the line, then drive forward.
  if (centerOnLine &&
      onLine == false)
  {
    motor.rightBrake();
    while (!rSen.check());
    motor.drive(fwdSpd);
    onLine = true;
  }
  
  // Okay, now we're "locked" to the line. We want to correct- if the
  //  center sensor is off the line but the right isn't, stop the right
  //  motor until center is back on. Vice versa for left.
  
  if (!cSen.check() &&
      onLine == true)
  {
    if (rSen.check())
    {
      motor.rightBrake();
      while (!cSen.check());
      motor.drive(fwdSpd);
    }
    else if (lSen.check())
    {
      motor.leftBrake();
      while (!cSen.check());
      motor.drive(fwdSpd);
    }
  }
}

