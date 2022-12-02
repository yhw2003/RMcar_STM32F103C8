#ifndef _MOTORDRIVER_H_
#define _MOTORDRIVER_H_

typedef struct _motorController
{
  int pin_A;
  int pin_B;
  int pin_E;
} MotorController;

extern void motorInit(MotorController * motorController);
[[deprecated("Move directly instead of turning")]]extern void goFront(MotorController * motorController);
[[deprecated("Move directly instead of turning")]]extern void goBack(MotorController * motorController);
[[deprecated("Move directly instead of turning")]]extern void turnRight(MotorController * motorController);
[[deprecated("Move directly instead of turning")]]extern void turnLeft(MotorController * motorController);

#endif