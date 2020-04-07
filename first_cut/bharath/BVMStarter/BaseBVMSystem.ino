int _currentSystemState = SYS_POWER_ON;
int _currentOperatingState = O_STOP;

  int getCurrentSystemState()
  {
    return _currentSystemState;
  }

  int getCurrentOperatingState()
  {
    _currentOperatingState;
  }
 
  int getLungPressure_cmH2O()
  {
      getSensorValue(SEN_PATIENT_INP_PRESSURE_CMH2O);
  }


 int isSafeForOperation(void)
 {
   return 1;  
 }

  void requestCalibration()
{
  
}
  
int isCalibrationDone(void)
{
  return 1;
}

void requestTravelToSystemReady(void)
{
}

bool systemReady()
{
  return true;
}

int isPatientReady(void)
{
  return 1;
}

void resetEarlierActuals()
{
  
}
void  requestSignalStartOperations()
{
  
}

void requestAwaitPatientReady()
{
  
}

void  hardStopMotor(void )
{
  
}
void  raiseAlarmLoop()
{
  
}

void requestLinearIncreaseToTargetTidalVolume()
{}

void coreBreathingLoop(void)
{
    /**
    check safety and issue system_stop
    check alarm and issue system_alarm
    if activate,
        decompress_bag();            
        wait_for_expiration_time(); 
        compress_bag();
            compress_till_pip;
            compress till TV is done;
        wait_for_pause_time();
        decompress_bag():
            open_up_till_peep;
                      
   */
   
}

void corePneumaticEventLoop()
{}

   void operatingEventLoop(void)
  {

      switch(_currentOperatingState)
      {
        case O_START_TO_STEADY:
                        if(acceptablyEqual(getParameter(P_TIDAL_VOLUME_LIMIT_ML),getLastStrokeValue(SEN_TIDAL_VOLUME_ML)))
                        _currentOperatingState = O_STEADY_STATE;
                        else
                          requestLinearIncreaseToTargetTidalVolume();
                          corePneumaticEventLoop();
                        break;
        case O_STEADY_STATE:   
                        coreBreathingLoop(); 
                        break;            
        
        case O_STOP:
        default:        //donothing();
                        break;                                    
                              
      }
          
   
  
  
}


void initPins()
{}



void doloop() {
  // put your main code here, to run repeatedly:

  switch(_currentSystemState)
  {
      case SYS_POWER_ON:
                
                _currentSystemState = SYS_AWAIT_CALIBRATION;
                requestCalibration();
                break;
      case SYS_AWAIT_CALIBRATION:      
                 if(isCalibrationDone())
                 {
                     _currentSystemState = SYS_TRAVEL_TO_SYSTEM_READY;
                     requestTravelToSystemReady();
                 }
                 break;
      case SYS_TRAVEL_TO_SYSTEM_READY:                
                  if(systemReady())
                  {
                      _currentSystemState = SYS_AWAIT_PATIENT_READY;
                      requestAwaitPatientReady();
                  }   
                 break;
      case SYS_AWAIT_PATIENT_READY:
                  if(isPatientReady())
                  {

                    _currentSystemState = SYS_SYSTEM_IN_OPERATION;
                    _currentOperatingState = O_START_TO_STEADY;
                     resetEarlierActuals(); 
                     requestSignalStartOperations();
                      
                  }
                 break;
      case SYS_SYSTEM_IN_OPERATION:
                    
                    operatingEventLoop();
                 break;
      case SYS_SYSTEM_IN_ERROR:
                  // RIGHT NOW, ONLY way to exit this is power cycling
                  hardStopMotor();
                  raiseAlarmLoop();
                  break;                  
      default:
              _currentSystemState = SYS_SYSTEM_IN_ERROR;
                break;
  }                            
  

}
