#include <Arduino.h>
#include "AutoPID.h"
#include "ATtiny_PWM.h"
#include "fold.h"
#define UNKOWN_PIN

const int targetSpeed = 100;
int realDutyCycle = 0.5;
int roundCnt = 0;

ATtiny_PWM* speed_controllers[4];


void setup() {
  attachInterrupt(UNKOWN_PIN,counter,FALLING);
  for (size_t i = 0; i < 4; i++)
  {
    speed_controllers[i] = new ATtiny_PWM(A0+i,1000.0f,dutyCycle(realDutyCycle));
  }
  
}

void loop() {
}

void counter() {
  roundCnt++;
}