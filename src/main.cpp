#include <Arduino.h>
#include "AutoPID.h"

class motor
{
private:
    /* data */
  uint32_t pinfst;
  uint32_t pinsec;

public:
  motor(uint32_t pin1, uint32_t pin2)
  {
      pinfst = pin1;
      pinsec = pin2;
      pinMode(pinfst,OUTPUT);
      pinMode(pinsec,OUTPUT);
      _stop();
  }
  void _stop(){
    digitalWrite(pinfst,LOW);
    digitalWrite(pinsec,LOW);
  }
  void goCW()
  {
    _stop();
    digitalWrite(pinfst,HIGH);
  }
  void goAntiCW()
  {
    _stop();
    digitalWrite(pinsec,HIGH);
  }
};

motor LFm(PA0,PA1);
motor RFm(PA2,PA3);
motor LBm(PA4,PA5);
motor RBm(PA6,PA7);

void go(motor * Tcar)
{
  for (size_t i = 0; i < 4; i++)
  {
    Tcar[i].goCW();
  }
}

void stop(motor * Tcar)
{
  for (size_t i = 0; i < 4; i++)
  {
    Tcar[i]._stop();
  }
  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(PB0,INPUT_PULLDOWN);

}

void loop() {
  // put your main code here, to run repeatedly:
  motor Tcar[] = {LFm,RFm,LBm,RBm};
  delay(100);
  while (1)
  {
    if (digitalRead(PB0))
    {
      stop(Tcar);
    } else
    {
      // break;
      go(Tcar);
    }
  }
}  