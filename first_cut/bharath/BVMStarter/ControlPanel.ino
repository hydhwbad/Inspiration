#include "bad.h"


//Parameters.ino
float parm_array[P_MAX_PARMS] = {
        0, // BUFFER
        12,   //RR
        300, 
        32, 
        95, 
        28, 
        5, 
        150, 
        33, 
        2, 
        1, 
        500, 
        C_SYS_MODE_CMV}; 

float getParameter(int i)
{
	return parm_array[i];
}

void displayAlarm(int i)
{
  
}

bool hasChanged(void)
{
  
  return true;
}

int getAvg(int p)
{
  int i, sum;
  float avg;
  sum=0;
   for(i = 0; i<10; i++)
   {
    sum +=analogRead(p);
   }
   avg = sum/10.0;
   return avg;
}

void readControlPanel()
{}

void readControlPanelx()
{
  int a0, a1;
  a0 = (getAvg(A0)/25)+4;
  a1 = (getAvg(A1)/25)*25+125;  
  parm_array[P_RESPIRATORY_RATE_PER_MIN]=a0;
  parm_array[P_TIDAL_VOLUME_LIMIT_ML]=a1;  
}

void updateDisplay(void)
{
  String sData;
  sData = "\n" + (int)getParameter(P_RESPIRATORY_RATE_PER_MIN);
  sData = sData  +" ";
  sData= sData +(int)getParameter(P_TIDAL_VOLUME_LIMIT_ML);
  Serial.println(sData);    
}
