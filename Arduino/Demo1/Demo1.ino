#include <RedBot.h>

RedBotMotor motor;

RedBotSensor lSen = RedBotSensor(A2);
RedBotSensor cSen = RedBotSensor(A3);
RedBotSensor rSen = RedBotSensor(A6);

RedBotAccel xl;

void setup()
{
  Serial.begin(57600);
}

void loop()
{
}

