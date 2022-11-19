typedef struct _motorController
{
  int pin_A;
  int pin_B;
  int pin_E;
} MotorController;

void motorInit(MotorController * motorController);
void goFront(MotorController * motorController);
void goBack(MotorController * motorController);
void turnRight(MotorController * motorController);
void turnLeft(MotorController * motorController);