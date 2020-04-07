//Breathe

#include "bad.h"



int bpm, b_millis, ier_pct, fwd_millis, rear_millis, fwd_stroke_millis, insp_pause_millis, rear_stroke_millis, exp_pause_millis, buffer_millis;
long t_millis=millis(), breath_count;
void debugParms(void)
{
      Serial.print("breath_count ");Serial.print(breath_count);
      Serial.print("time_elapsed ");Serial.print((millis()-t_millis)/1000);
      Serial.print(" bpm: ");Serial.print(bpm);
      Serial.print(" tv: ");Serial.print(getParameter(P_TIDAL_VOLUME_LIMIT_ML));
      Serial.print(" ier: ");Serial.print(ier_pct);
      Serial.print(" b_millis: ");Serial.print(b_millis);
      Serial.print(" fwd: "); Serial.print(fwd_stroke_millis);
      Serial.print(" back: "); Serial.print(rear_stroke_millis);
      Serial.print(" insp_pause: "); Serial.print(insp_pause_millis);
      Serial.print(" exp_pause: "); Serial.print(exp_pause_millis);
      Serial.print(" steps: "); Serial.print(getStrokeSteps());
      Serial.println("");
}

void initBreathParams(void)
{
  
  unsigned short  s, tv;

     bpm = getParameter(P_RESPIRATORY_RATE_PER_MIN);
     ier_pct = getParameter(P_IE_RATIO_PERCENTAGE);
     insp_pause_millis = getParameter(P_COMPRESS_EXPAND_DELAY_MILLIS);
     exp_pause_millis = getParameter(P_EXPIRATION_TIME_LIMIT_MILLIS);
     b_millis = 60000/bpm;
     
     fwd_millis = b_millis*(ier_pct/100.0);
     rear_millis = b_millis - fwd_millis;
     fwd_stroke_millis = fwd_millis - insp_pause_millis;
     rear_stroke_millis = rear_millis - exp_pause_millis; 
     
     tv = getParameter(P_TIDAL_VOLUME_LIMIT_ML);  
     s = getStepsForTidalVolume(tv);
     initStrokeParams(getStepsHomeFromStart(),s,fwd_stroke_millis, rear_stroke_millis);
     buffer_millis = 2;
     
}


boolean inspirationDetected(void)
{
  static boolean idFlag = false;
  static long idTime = 0;
  long cTime;
  
  if(idFlag == false && idTime == 0)
  {
    idTime = millis();    
  }
  
  cTime = millis();
    
  if(getSensorValue(SEN_PATIENT_INP_PRESSURE_CMH2O) < (getParameter(P_PEEP_CMH2O)- getParameter(P_TRIGGER_SENSITIVITY_PRESSURE_CMH2O)))
  {
    idFlag = true;
  }
  else
  if(cTime - idTime > getParameter(P_EXPIRATION_TIME_LIMIT_MILLIS))
  {
    idFlag = true;
  }

  return idFlag;
  
}

void Breathe()
{
    int i;
    long t_non_rt0, t_non_rt1, t_rt0, t_rt1;
    bool uiChanged;
      uiChanged = false;      
      if(hasChanged())
      {
        readControlPanel();
        uiChanged = true;
      }        
      readSensors();
      updateDisplay();      
      //if(uiChanged)
        initBreathParams();

      checkSystemSafety();
              
      // assert motor off
      // assert at begin of stroke

      //
      //breathStage = 
      
      //debugParms();      
      if(getAlarmState()==SYS_SAFETY_STOP)
        return;

      setValves(BREATHE_BEGIN_INSPIRATION);
      compress();
      
      for(i = 0; i<(fwd_stroke_millis+buffer_millis); i++)
      {
          delay(1);
          compressionRefresh();
      }
      
    /*
      for(i = 0; i<2010; i++)
      {
          delay(1);
          compressionRefresh();
      }
      */
      setValves(BREATHE_POST_INSPIRATION_PAUSE);
      delay(getParameter(P_COMPRESS_EXPAND_DELAY_MILLIS));
      setValves(BREATHE_BEGIN_EXPIRATION);
      expand();
      

      
      for(i = 0; i<(rear_stroke_millis+buffer_millis); i++)
      {
          delay(1);
          compressionRefresh();
      }
      setValves(BREATHE_POST_EXPIRATION_PAUSE);
      /*
      for(i = 0; i<2010; i++)
      {
          delay(1);
          compressionRefresh();
      }    
      */
      breath_count++;   
}
