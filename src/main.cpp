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

_Bool sL = 0;
_Bool sR = 0;

void leL()
{
  sL = 1;
}

void leR()
{
  sR = 1;
}

void leLu()
{
  sL = 0;
}

void leRu()
{
  sR = 0;
}

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

int St = 0;
void TR()
{
  if (St == 0){
  turnRight(motorController);
  }
}
void TL()
{
  if (St == 0){
  turnLeft(motorController);
  }
}

void setup() {
  //Init speed controller for each wheel
  motorInit(motorController);
  //Init speed sensor
  //init road scanner
  pinMode(sensor_pin_A, INPUT);
  pinMode(sensor_pin_B, INPUT);
  pinMode(L_E, INPUT);
  pinMode(R_E, INPUT);
  pinMode(OUTPUT_pin, OUTPUT);
  pinMode(GET_pin, INPUT_PULLDOWN);
  attachInterrupt(sensor_pin_A, leL, RISING);
  attachInterrupt(sensor_pin_B, leR, RISING);
  // attachInterrupt(sensor_pin_A, leLu, FALLING);
  // attachInterrupt(sensor_pin_B, leRu, FALLING);
  attachInterrupt(L_E, TR, RISING);
  attachInterrupt(R_E, TL, RISING);
  digitalWrite(OUTPUT_pin, LOW);
  stopHere(motorController);
  analogWriteFrequency(50);
  for (int i = 0; i < 4; i++)
  {
  analogWrite(motorController[i].pin_E, 200);
  }
}

_Bool started = 0;

void loop() {
  //update speed
  if (!started)
  {
    started = 1;
    delay(500);
  }
  if (St == 0)
  {
    if (down == 0 && sL == 0 && sR == 0)
    {
      goNorth(motorController);
    } else if (sL == 1 && sR == 1)
    {
      goNorth(motorController);
      St = 1;
      if (down == 0) {
      delay(800);
      }
      stopHere(motorController);
      digitalWrite(OUTPUT_pin, HIGH);
      while (!digitalRead(GET_pin));
      goEast(motorController);
      while (digitalRead(sensor_MID_pin));
      sL = 0;
      sR = 0;
      goNorth(motorController);
      down = 1;
    }
  }


  //update state

}