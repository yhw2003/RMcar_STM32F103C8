#include <Arduino.h>
#include "arduino-timer.h"
#include "AutoPID.h"
#include "ATtiny_PWM.h"
#include "fold.h"
#include "config.h"
#include "PIDconfig.h"


const int targetSpeed = 100;
double realDutyCycle = 0.5;
int roundCnt = 0;
double speed = 0;

ATtiny_PWM ** speed_controllers;

auto timer  = timer_create_default();


AutoPID ** PidController;



void calculate()
{
  speed = roundCnt/0.5;
  roundCnt = 0;
}


void counter() {
  roundCnt++;
}

void setup() {
  //Init speed sensor
  attachInterrupt(LF_scanner_pin,counter,FALLING);
  attachInterrupt(RF_scanner_pin,counter,FALLING);
  attachInterrupt(LB_scanner_pin,counter,FALLING);
  attachInterrupt(RB_scanner_pin,counter,FALLING);
  //init PID controller for each wheel
  for (size_t i = 0; i < 4; i++)
  {
    speed_controllers[i] = new ATtiny_PWM(A0+i,1000.0f,dutyCycle(realDutyCycle));
  }
  
  //Init speed controller for each wheel
  for (size_t i = 0; i < 4; i++)
  {
    PidController[i] = new AutoPID(&speed,(double *)&targetSpeed,&realDutyCycle,0.0,1.0,(double)Ki,(double)Kp,(double)Kd);
  }
}

void loop() {
  for (size_t i = 0; i < 4; i++)
  {
    PidController[i]->run();
  }

  /*
  Other codes
  */
  
  timer.tick();
}
