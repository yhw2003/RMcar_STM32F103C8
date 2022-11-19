#include <Arduino.h>
// #include "arduino-timer.h"
#include "AutoPID.h"
// #include "ATtiny_PWM.h"
// #include "PWMServo.h"
#include "fold.h"
#include "config.h"
#include "PIDconfig.h"
#include "STM32TimerInterrupt.h"
#include "STM32_ISR_Timer.h"
#define MS 50

const double targetSpeed = 100;
double realDutyCycle[4] = {0.6,0.6,0.6,0.6};
int roundCnt[4] = {0};
double speed[4] = {0};
STM32Timer ITimer(TIM1);
STM32_ISR_Timer ISR_Timer;

// PWMServo ** speed_controllers;

// auto timer  = timer_create_default();

AutoPID ** PidController;



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
  //Init speed sensor
  attachInterrupt(LF_scanner_pin,counterLF,FALLING);
  attachInterrupt(RF_scanner_pin,counterRF,FALLING);
  attachInterrupt(LB_scanner_pin,counterLB,FALLING);
  attachInterrupt(RB_scanner_pin,counterRB,FALLING);
  pinMode(LF_E_pin,OUTPUT);
  pinMode(RF_E_pin,OUTPUT);
  pinMode(LB_E_pin,OUTPUT);
  pinMode(RB_E_pin,OUTPUT);
  analogWriteFrequency(7200);
  //Init speed controller for each wheel


  for (size_t i = 0;!speed && i < 4; i++)
  {
    PidController[i] = new AutoPID(&speed[i],(double *)&targetSpeed,&realDutyCycle[i],0.0,1.0,Ki,Kp,Kd);
  }
  while (!ITimer.attachInterruptInterval(MS * 1000, TimerHandler))
  {
    continue;
  }
  ISR_Timer.setInterval(500L,calcRUN);
}

void loop() {
  for (size_t i = 0; i < 4; i++)//PID update
  {
    PidController[i]->run();
  }
  {//update speed
  analogWrite(LF_E_pin,dutyCycle(realDutyCycle[LF]));
  analogWrite(RF_E_pin,dutyCycle(realDutyCycle[RF]));
  analogWrite(LB_E_pin,dutyCycle(realDutyCycle[LB]));
  analogWrite(RB_E_pin,dutyCycle(realDutyCycle[RB]));
  }
  

  /*
  Other codes
  */
  
  // timer.tick();
}
