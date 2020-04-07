#include "bad.h"


void raiseAlarm(int i)
{
    
  
}

int getAlarmState(void)
{
  return SYS_SAFETY_SAFE;
}

void checkSystemSafety(void)
{
  if(getCurrentSystemState()==SYS_SYSTEM_IN_OPERATION)
  {
      if(getLastStrokeValue(SEN_PATIENT_INP_PRESSURE_CMH2O)>=getParameter(P_PLATEAU_PRESSURE_ULIMIT_CMH2O))
      {
        raiseAlarm(PP_ALARM);
      }
      else if(getLastStrokeValue(SEN_TIDAL_VOLUME_ML) < getParameter(P_TIDAL_VOLUME_LIMIT_ML) && getCurrentOperatingState()==O_STEADY_STATE)
      {
        raiseAlarm(TV_ALARM);
      }
      else if(getLastStrokeValue(SEN_O2_CONC_PERCENTAGE) < getParameter(P_FIO2_PERCENTAGE))
      {
         raiseAlarm(O2_ALARM);
      }
  }
}

int checkSystemSafety_Compression(void)
{
  if(getSensorValue(SEN_PATIENT_INP_PRESSURE_CMH2O) < getParameter(P_BACK_PRESSURE_LIMIT_CMH2O))
      return SYS_SAFETY_SAFE;
  else
      return SYS_SAFETY_STOP;
}
