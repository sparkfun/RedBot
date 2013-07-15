#include <RedBot.h>

RedBotAccel accel;

void setup()
{
  Serial.begin(115200);
  pinMode(14, INPUT_PULLUP);
  //accel.enableTap();
}

void loop()
{
 /* while (Serial.available() == 0);
  Serial.read();
  Serial.print("Waiting...");
  while(1)
  {
    if (accel.checkTap())
    {
      Serial.println("Tap!");
      break;
    }
  }*/
  
  while (digitalRead(14) == HIGH);
  delay(250);
  while (digitalRead(14) == LOW)
  {
    accel.read();
    Serial.print(accel.x); Serial.print(",");
    Serial.print(accel.y); Serial.print(",");
    Serial.print(accel.z); Serial.print("\n");
  }
  Serial.print('x');
}
