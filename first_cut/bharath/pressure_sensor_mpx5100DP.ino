#include "pinout.h"

float _rho, _a1, _a2, mFactor, mFactor_lpm;

//A1>A2, P1>P2: Flow 1 -> 2 
void setVenturi(float rho, float a1, float a2)
{
  _rho = rho;
  _a1 = a1;
  _a2 = a2;
  mFactor = _a2*sqrt(2)*1/sqrt(_rho*(1-(a2/a1)*(a2/a1)));
  mFactor_lpm = mFactor*1000*60;
}

float getFlowRate_m3ps(float diffPressure)
{
  return sqrt(diffPressure)*mFactor;
}

float getFlowRate_lpm(float diffPressure)
{
  return sqrt(diffPressure)*mFactor_lpm;
}

float getAvg(int chno, int samples) {
  analogReference(EXTERNAL);
  float Avg = 0;
  float smplData[samples];
  float AvgHigh;
  float AvgLow;
  float adcfilt;
  int count;
  for (int loop1 = 0; loop1 < samples; loop1++){
    smplData[loop1] = analogRead(chno) ;
    Avg = Avg + smplData[loop1];
   }
  
  Avg = Avg/samples;
  AvgHigh = Avg + 50;
  AvgLow = Avg - 50;
  count =0;
  adcfilt = 0;
  for (int loop2 = 0; loop2 < samples; loop2 ++){
    if (smplData[loop2] > AvgLow) {
        if (smplData[loop2] < AvgHigh){
          adcfilt = adcfilt + smplData[loop2];
          count = count + 1;
        }
      }
    }
    if (count > 0) {
      adcfilt = adcfilt/count;
    }
     else{
        adcfilt = Avg;
        //Serial.print("D Avg ");
      }
    return adcfilt;
}

float getAvgg(int chno, int samples) {

  int i=0, tot=0;
  for(i=0; i<samples; i++)
    tot+= analogRead(chno);
  return (1.0*tot)/samples;
}

void setup() {
  // put your setup code here, to run once:
  float r1,r2,a1, a2, rho;
  Serial.begin(9600);
  r1 = 19.5/2.0; r1 = r1/100;
  r2 = 9.5/2.0; r2 = r2/100;
  a1 = PI*r1*r1;
  a2 = PI*r2*r2;
  rho = 1.429/(1000*1000);
  setVenturi(rho,a1, a2);
}

void loop() {
  // put your main code here, to run repeatedly:
  short reading1 = 0, reading2;
  float vout1, pres1, flr1;
//  Utils u;

//   //reading = (short)utils.readPin(A4, 25);
    reading1 = analogRead(A0);//getAvg(A5,10);
    reading1 = getAvgg(A0, 10);
    vout1 = (reading1/1023.0)*5.0;
    pres1 = (vout1*5.0)*22.22 - 0.44;
 //   flr1 = getFlowRate_lpm(reading1);
    
    //reading1 = getAvg(A5,20);
    //reading2 = getAvg(A4,20);
   Serial.print(reading1);
   Serial.print(" ");
   Serial.print(vout1);
   Serial.print(" ");
   Serial.println(pres1);
   
   
   /*
   Serial.print(" ");
   
   Serial.print(vout1);
   Serial.print(" ");
   Serial.print(pres1);
   Serial.print(" ");
   Serial.println(flr1);
   */
   //Serial.print(" ");
   //Serial.println(reading2);
   
   delay(1000);
    
}
