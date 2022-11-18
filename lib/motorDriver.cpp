#include <Arduino.h>
#include "motorDriver.h"

void goFront(MotorController ** motorController)
{
  for (size_t i = 0; i < 4; i++)
  {
  digitalWrite(motorController[i]->pin_A,HIGH);
  digitalWrite(motorController[i]->pin_B,LOW);
  }
}

void goBack(MotorController ** motorController)
{
  for (size_t i = 0; i < 4; i++)
  {
  digitalWrite(motorController[i]->pin_A,LOW);
  digitalWrite(motorController[i]->pin_B,HIGH);
  }
}

void turnLeft(MotorController ** motorController)
{
  
}