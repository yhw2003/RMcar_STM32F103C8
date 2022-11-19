#include <Arduino.h>
#include "motorDriver.h"
#include "fold.h"
#define _round 50
#define degree(x) ((x) * _round)


void motorInit(MotorController * motorController)
{
  for (size_t i = 0; i < 4; i++)
  {
    pinMode(motorController[i].pin_A,OUTPUT);
    pinMode(motorController[i].pin_B,OUTPUT);
    pinMode(motorController[i].pin_E,OUTPUT);
  }
  
}

void goFront(MotorController * motorController)
{
  for (size_t i = 0; i < 4; i++)
  {
    digitalWrite(motorController[i].pin_A,HIGH);
    digitalWrite(motorController[i].pin_B,LOW);
  }
}

void goBack(MotorController * motorController)
{
  for (size_t i = 0; i < 4; i++)
  {
  digitalWrite(motorController[i].pin_A,LOW);
  digitalWrite(motorController[i].pin_B,HIGH);
  }
}

void turnLeft(MotorController * motorController, int * degreeCnt)
{
  *degreeCnt = 0;
  digitalWrite(motorController[LF].pin_A,LOW);
  digitalWrite(motorController[LF].pin_B,HIGH);
  digitalWrite(motorController[LB].pin_A,LOW);
  digitalWrite(motorController[LB].pin_B,HIGH);
  digitalWrite(motorController[RF].pin_A,HIGH);
  digitalWrite(motorController[RF].pin_B,LOW);
  digitalWrite(motorController[RB].pin_A,HIGH);
  digitalWrite(motorController[RB].pin_B,LOW);
  while (*degreeCnt >= degree(90)){continue;}
  goFront(motorController);
}

void turnRight(MotorController * motorController, int * degreeCnt)
{
  *degreeCnt = 0;
  digitalWrite(motorController[RF].pin_A,LOW);
  digitalWrite(motorController[RF].pin_B,HIGH);
  digitalWrite(motorController[RB].pin_A,LOW);
  digitalWrite(motorController[RB].pin_B,HIGH);
  digitalWrite(motorController[LF].pin_A,HIGH);
  digitalWrite(motorController[LF].pin_B,LOW);
  digitalWrite(motorController[LB].pin_A,HIGH);
  digitalWrite(motorController[LB].pin_B,LOW);
  while (*degreeCnt >= degree(90)){continue;}
  goFront(motorController);
}