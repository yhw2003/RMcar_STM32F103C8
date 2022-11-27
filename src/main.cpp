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
enum status {
  TURN_LEFT, TURN_RIGHT, GO_STRAIGHT
};

enum status St = GO_STRAIGHT;

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

void _LEFT(){
  if (digitalRead(sensor_LO_pin))
  {
    St = TURN_LEFT;
  }
}
void _RIGHT(){
  if (digitalRead(sensor_RO_pin))
  {
    St = TURN_RIGHT;
  }
  
}
void _STRAIGHT(){
  St = GO_STRAIGHT;
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
  attachInterrupt(LF_scanner_pin,counterLF,FALLING);
  attachInterrupt(RF_scanner_pin,counterRF,FALLING);
  attachInterrupt(LB_scanner_pin,counterLB,FALLING);
  attachInterrupt(RB_scanner_pin,counterRB,FALLING);
  analogWriteFrequency(7200);
  //init road scanner
  pinMode(sensor_LO_pin,OUTPUT);
  pinMode(sensor_LI_pin,OUTPUT);
  pinMode(sensor_MID_pin,OUTPUT);
  pinMode(sensor_RI_pin,OUTPUT);
  pinMode(sensor_RO_pin,OUTPUT);
  // attachInterrupt(sensor_LO_pin,counterLF,FALLING);
  attachInterrupt(sensor_LI_pin,_LEFT,FALLING);
  // attachInterrupt(sensor_MID_pin,counterLB,FALLING);
  attachInterrupt(sensor_RI_pin,_RIGHT,FALLING);
  // attachInterrupt(sensor_RO_pin,counterRB,FALLING);




  for (size_t i = 0;!speed && i < 4; i++)
  {
    PidController[i] = new AutoPID(&speed[i],(double *)&targetSpeed,&realDutyCycle[i],0.0,1.0,Ki,Kp,Kd);
  }
  while (!ITimer.attachInterruptInterval(MS * 1000, TimerHandler))
  {
    continue;
    //wait for pwm init
  }
  ISR_Timer.setInterval(500L,calcRUN);
  
}

void loop() {
  for (size_t i = 0; i < 4; i++)//PID update
  {
    PidController[i]->run();
  }
  {//update speed
  analogWrite(LF_E_pin,128);
  analogWrite(RF_E_pin,128);
  analogWrite(LB_E_pin,128);
  analogWrite(RB_E_pin,128);
  }
  goFront(motorController);
}
