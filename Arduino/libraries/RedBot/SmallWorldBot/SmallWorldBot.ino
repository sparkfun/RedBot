#include <RedBot.h>

RedBotMotor motor;

void setup()
{
  tone(9, 440, 1000);
  pinMode(14, INPUT);
  delay(15000);
}

#define beatLength 500
#define WN      beatLength*4
#define HN      beatLength*2
#define QN      beatLength
#define EN      beatLength/2
#define SN      beatLength/4

void loop()
{
  while(digitalRead(14) == LOW);
  delay(2000);
  motor.drive(125);
  smallWorld();
  delay(500);  
}

void playNote(int note, int length)
{
  tone(9, note, length);
  delay(length);
}
