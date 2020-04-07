#include "pinout.h"
#include "bad.h"

void setupStepper(void);
void travelRequest(int dir, int steps, long time_limit_millis);
void refresh(void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupStepper();
  
}




void loopTV() {
  // put your main code here, to run repeatedly:
  int i;
  int    bpm = 12;
  int tv = 400;
  int l_steps;
  int time_millis;
  float ratio = 500.0/200.0; // 500 millis per 200 steps 
      l_steps = getStepsForTidalVolume(tv);
      /*
      Serial.print("TV steps : ");//+l_steps);
      Serial.println(l_steps);
      Serial.print("mm : ");
      Serial.println((l_steps/200.0)*8);
      */
      time_millis  = ratio*l_steps +1;
      travelRequest(HIGH, l_steps, time_millis);
      for(i = 0; i<time_millis + 2; i++)
      {
          delay(1);
          refresh();
      }
      while(getStepsMoved() <l_steps)
        delay(1);
      travelRequest(LOW, l_steps, time_millis);
      for(i = 0; i<time_millis + 2; i++)
      {
          delay(1);
          refresh();
      }
      
      delay(5000);

}


void loop()
{
  loopTV();
}
void goodLoop() {
  // put your main code here, to run repeatedly:
  int i;
      travelRequest(HIGH, 200, 500);
      for(i = 0; i<2010; i++)
      {
          delay(1);
          refresh();
      }
      delay(5000);

}

void loopz()
{
  if(getParameter(P_SYSTEM_MODE_ENUM)==C_SYS_MODE_ASSIST)
  {
    while(!inspirationDetected())
     delay(1);
  }
  else
    delay(getParameter(P_EXPIRATION_TIME_LIMIT_MILLIS));
  Breathe();
      
}

/*
void loopx()
{
  testloop();
}
*/
