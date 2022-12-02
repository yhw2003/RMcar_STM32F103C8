#include <Arduino.h>
// #include "arduino-timer.h"
#include "AutoPID.h"
// #include "ATtiny_PWM.h"
// #include "PWMServo.h"
#include "fold.h"
#include "config.h"
#include "PIDconfig.h"
#include "motorDriver.c"
#include "wayFinding.c"
#include "STM32TimerInterrupt.h"
#include "STM32_ISR_Timer.h"
#define MS 50

_Bool down = 0;

Direct _St = N;

void le()
{
  _St = S;
}

const double targetSpeed = 100;
double realDutyCycle[4] = {0.6,0.6,0.6,0.6};
int roundCnt[4] = {0};
int degreeCnt = 0;
double speed[4] = {0};
STM32Timer ITimer(TIM1);
STM32_ISR_Timer ISR_Timer;
AutoPID ** PidController;
MotorController motorController[4] = {
  {
    .pin_A = LF_control_pin_A,
    .pin_B = LF_control_pin_B,
    .pin_E = LF_E_pin
  },
  {
    .pin_A = RF_control_pin_A,
    .pin_B = RF_control_pin_B,
    .pin_E = RF_E_pin
  },
  {
    .pin_A = LB_control_pin_A,
    .pin_B = LB_control_pin_B,
    .pin_E = LB_E_pin
  },
  {
    .pin_A = RB_control_pin_A,
    .pin_B = RB_control_pin_B,
    .pin_E = RB_E_pin
  }
};

position targets[8] = 
{
  {
    .x = 11,
    .y = 8
  },
  {//1号目标
    .x = 1,
    .y = 0
  },
  {//2号目标
    .x = 3,
    .y = 0
  },
  {//3号目标
    .x = 5,
    .y = 0
  },
  {//4号目标
    .x = 7,
    .y = 0
  },
  {//5号目标
    .x = 9,
    .y = 0
  },
  {//6号目标
    .x = 11,
    .y = 0
  }
};

position startPOS = {
  .x = 11,
  .y = 8
};

void calculateLF()
{
  speed[LF] = roundCnt[LF]/0.5;
  roundCnt[LF] = 0;
}
void calculateLB()
{
  speed[LB] = roundCnt[LB]/0.5;
  roundCnt[LB] = 0;
}
void calculateRF()
{
  speed[RF] = roundCnt[RF]/0.5;
  roundCnt[RF] = 0;
}
void calculateRB()
{
  speed[RB] = roundCnt[RB]/0.5;
  roundCnt[RB] = 0;
}


void counterLF() {
  roundCnt[LF]++;
}
void counterRF() {
  roundCnt[RF]++;
}
void counterLB() {
  roundCnt[LB]++;
}
void counterRB() {
  roundCnt[RB]++;
}


void TimerHandler()
{
  ISR_Timer.run();
}

void calcRUN()
{
  calculateLF();
  calculateLB();
  calculateRF();
  calculateRB();
}

void setup() {
  //Init speed controller for each wheel
  motorInit(motorController);
  //Init speed sensor
  //init road scanner
  pinMode(sensor_pin, INPUT);
  pinMode(OUTPUT_pin, OUTPUT);
  pinMode(GET_pin, INPUT_PULLDOWN);
  attachInterrupt(sensor_pin, le, RISING);
  digitalWrite(OUTPUT_pin, LOW);
  stopHere(motorController);
  
}

void loop() {
  //update speed
if (down == 0 && _St == N)
{
  delay(500);
  goNorth(motorController);
} else if (_St == S)
{
  goWest(motorController);
  delay(500);
  goNorth(motorController);
  delay(200);
  stopHere(motorController);
  digitalWrite(OUTPUT_pin, HIGH);
  while (!digitalRead(GET_pin));
  goSouth(motorController);
  delay(200);
  goEast(motorController);
  delay(1000);
  goNorth(motorController);
  delay(3000);
  
}


  //update state

}