#include "RedBot.h"
#include <Arduino.h>

RedBotMotor::RedBotMotor()
{
  pinMode(R_CTRL_1, OUTPUT);
  pinMode(R_CTRL_2, OUTPUT);
  pinMode(L_CTRL_1, OUTPUT);
  pinMode(L_CTRL_2, OUTPUT);
}

void RedBotMotor::stop()
{
  leftStop();
  rightStop(); 
}

void RedBotMotor::brake()
{
  leftBrake();
  rightBrake(); 
}

void RedBotMotor::drive(int speed)
{
  if (speed > 0)
  {
    leftFwd((byte)(abs(speed)));
    rightFwd((byte)(abs(speed)));
  }
  else
  {
    leftRev((byte)(abs(speed)));
    rightRev((byte)(abs(speed)));
  }
}

void RedBotMotor::pivot(int speed)
{
  if (speed > 0)
  {
    leftRev((byte)(abs(speed)));
    rightFwd((byte)(abs(speed)));
  }
  else
  {
    leftFwd((byte)(abs(speed)));
    rightRev((byte)(abs(speed)));
  }
}

void RedBotMotor::rightDrive(int speed)
{
  if (speed > 0)
  {
    rightFwd((byte)(abs(speed)));
  }
  else
  {
    rightRev((byte)(abs(speed)));
  }
}

void RedBotMotor::leftDrive(int speed)
{
  if (speed > 0)
  {
    leftFwd((byte)(abs(speed)));
  }
  else
  {
    leftRev((byte)(abs(speed)));
  }
}

void RedBotMotor::leftBrake()
{
  digitalWrite(L_CTRL_1, HIGH);
  digitalWrite(L_CTRL_2, HIGH);
  analogWrite(PWM_L, 0);
}

void RedBotMotor::rightBrake()
{
  digitalWrite(R_CTRL_1, HIGH);
  digitalWrite(R_CTRL_2, HIGH);
  analogWrite(PWM_R, 0);
}

void RedBotMotor::leftStop()
{
  digitalWrite(L_CTRL_1, LOW);
  digitalWrite(L_CTRL_2, LOW);
  analogWrite(PWM_L, 0);
}

void RedBotMotor::rightStop()
{
  digitalWrite(R_CTRL_1, LOW);
  digitalWrite(R_CTRL_2, LOW);
  analogWrite(PWM_R, 0);
}

/******************************************************************************
Private functions for RedBotMotor
******************************************************************************/

void RedBotMotor::leftFwd(byte spd)
{
  digitalWrite(L_CTRL_1, HIGH);
  digitalWrite(L_CTRL_2, LOW);
  analogWrite(PWM_L, spd);
}

void RedBotMotor::leftRev(byte spd)
{
  digitalWrite(L_CTRL_1, LOW);
  digitalWrite(L_CTRL_2, HIGH);
  analogWrite(PWM_L, spd);
}

void RedBotMotor::rightFwd(byte spd)
{
  digitalWrite(R_CTRL_1, HIGH);
  digitalWrite(R_CTRL_2, LOW);
  analogWrite(PWM_R, spd);
}

void RedBotMotor::rightRev(byte spd)
{
  digitalWrite(R_CTRL_1, LOW);
  digitalWrite(R_CTRL_2, HIGH);
  analogWrite(PWM_R, spd);
}
