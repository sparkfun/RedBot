void driveDist(byte spd, int dist)
{
  long startTime = millis();
  long currTime = startTime;
  if (dist < 0) driveRev(spd);
  else          driveFwd(spd);
  if (dist < 0) dist *= -1;
  int lTicks = 0;
  int rTicks = 0;
  boolean rState[2];
  boolean lState[2];
  while ((lTicks < dist) || (rTicks < dist))
  {
    currTime = millis();
    if ((currTime - startTime) > MOTION_TIMEOUT)
    {
      driveBrake();
      XBee.println("Motion timeout!");
      break;
    }
    if ((sensorScan() != 0) && (noLine != false))
    {
      driveBrake();
      XBee.println("Boundary error!");
      break;
    }
    rState[1] = rState[0];
    lState[1] = lState[0];
    if (digitalRead(R_ENC) == HIGH) rState[0] = true;
    else                            rState[0] = false;
    if (digitalRead(L_ENC) == HIGH) lState[0] = true;
    else                            lState[0] = false;
    if ((rState[0] && !rState[1])==true) rTicks++;
    if ((lState[0] && !lState[1])==true) lTicks++;
    if (lTicks == dist) leftBrake();
    if (rTicks == dist) rightBrake();
  }
}

void driveTurn(int lDist, int rDist)
{
  long startTime = millis();
  long currTime = startTime;
  if (lDist < 0) leftRev(255);
  else           leftFwd(255);
  if (rDist < 0) rightRev(255);
  else           rightFwd(255);
  if (lDist < 0) lDist *= -1;
  if (rDist < 0) rDist *= -1;
  int lTicks = 0;
  int rTicks = 0;
  boolean rState[2];
  boolean lState[2];
  while ((lTicks < lDist) || (rTicks < rDist))
  {
    currTime = millis();
    if ((currTime - startTime) > MOTION_TIMEOUT)
    {
      driveBrake();
      XBee.println("Motion timeout!");
      break;
    }
    if ((sensorScan() != 0) && (noLine != false))
    {
      driveBrake();
      XBee.println("Boundary error!");
      break;
    }
    rState[1] = rState[0];
    lState[1] = lState[0];
    if (digitalRead(R_ENC) == HIGH) rState[0] = true;
    else                            rState[0] = false;
    if (digitalRead(L_ENC) == HIGH) lState[0] = true;
    else                            lState[0] = false;
    if ((rState[0] && !rState[1])==true) 
    {
      rTicks++;
      XBee.print("R Ticks: "); XBee.println(rTicks);
    }
    if ((lState[0] && !lState[1])==true)
    {
      lTicks++;
      XBee.print("L Ticks: "); XBee.println(lTicks);
    }
    if (lTicks == lDist) leftBrake();
    if (rTicks == rDist) rightBrake();
  }
}

void driveStop()
{
  leftStop();
  rightStop(); 
}

void driveBrake()
{
  leftBrake();
  rightBrake(); 
}

void driveFwd(byte spd)
{
  leftFwd(spd);
  rightFwd(spd);
}

void driveRev(byte spd)
{
  leftRev(spd);
  rightRev(spd);
}

void leftFwd(byte spd)
{
  digitalWrite(L_CTRL_1, HIGH);
  digitalWrite(L_CTRL_2, LOW);
  analogWrite(PWM_L, spd);
}

void leftRev(byte spd)
{
  digitalWrite(L_CTRL_1, LOW);
  digitalWrite(L_CTRL_2, HIGH);
  analogWrite(PWM_L, spd);
}

void rightFwd(byte spd)
{
  digitalWrite(R_CTRL_1, HIGH);
  digitalWrite(R_CTRL_2, LOW);
  analogWrite(PWM_R, spd);
}

void rightRev(byte spd)
{
  digitalWrite(R_CTRL_1, LOW);
  digitalWrite(R_CTRL_2, HIGH);
  analogWrite(PWM_R, spd);
}

void leftBrake()
{
  digitalWrite(L_CTRL_1, HIGH);
  digitalWrite(L_CTRL_2, HIGH);
  analogWrite(PWM_L, 0);
}

void rightBrake()
{
  digitalWrite(R_CTRL_1, HIGH);
  digitalWrite(R_CTRL_2, HIGH);
  analogWrite(PWM_R, 0);
}

void leftStop()
{
  digitalWrite(L_CTRL_1, LOW);
  digitalWrite(L_CTRL_2, LOW);
  analogWrite(PWM_L, 0);
}

void rightStop()
{
  digitalWrite(R_CTRL_1, LOW);
  digitalWrite(R_CTRL_2, LOW);
  analogWrite(PWM_R, 0);
}
