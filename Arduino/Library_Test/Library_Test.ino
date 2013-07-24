#include <RedBot.h>

RedBotAccel accel;
RedBotMotor motor;
RedBotSensor leftSen = RedBotSensor(A0);
RedBotSensor midSen = RedBotSensor(A1);
RedBotSensor rightSen = RedBotSensor(A2);

void setup()
{
  Serial.begin(115200);
}

void loop()
{

}
