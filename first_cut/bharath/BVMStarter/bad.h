#ifndef BREATHING_ASSIST_DEVICE_H
#define BREATHING_ASSIST_DEVICE_H 1
// Sensors
#define SEN_PATIENT_INP_PRESSURE_CMH2O      1
#define SEN_TIDAL_VOLUME_ML                 2
#define SEN_O2_CONC_PERCENTAGE              3

#define P_RESPIRATORY_RATE_PER_MIN            1          
#define P_TIDAL_VOLUME_LIMIT_ML               2
#define P_BACK_PRESSURE_LIMIT_CMH2O           3
#define P_FIO2_PERCENTAGE                     4
#define P_PLATEAU_PRESSURE_ULIMIT_CMH2O       5
#define P_PEEP_CMH2O                          6
#define P_COMPRESS_EXPAND_DELAY_MILLIS        7
#define P_IE_RATIO_PERCENTAGE                 8
#define P_TRIGGER_SENSITIVITY_PRESSURE_CMH2O  9
#define P_PEEP_ENABLED_FLAG                   10
#define P_EXPIRATION_TIME_LIMIT_MILLIS        11
#define P_SYSTEM_MODE_ENUM                    12
#define P_MAX_PARMS                           13

#define C_SYS_MODE_CMV 1
#define C_SYS_MODE_ASSIST 2

#define S_TV_PER_STEP


#define PP_ALARM      1
#define TV_ALARM      2
#define O2_ALARM      3

#define SYS_SAFETY_SAFE      1
#define SYS_SAFETY_WARNING   2
#define SYS_SAFETY_STOP      3


#define SYS_COMPRESS_ALARM 0x01
#define SYS_STROKE_ALARM 0x02
#define SYS_FWD_STOP_ALARM 0x04
#define SYS_REV_STOP_ALARM 0x08

#define BREATHE_BEGIN_INSPIRATION       1
#define BREATHE_POST_INSPIRATION_PAUSE  2
#define BREATHE_BEGIN_EXPIRATION        3
#define BREATHE_POST_EXPIRATION_PAUSE   4


#define SYS_POWER_ON                    1
#define SYS_SYSTEM_IN_OPERATION         2
#define SYS_AWAIT_CALIBRATION           3
#define SYS_TRAVEL_TO_SYSTEM_READY      4
#define SYS_AWAIT_PATIENT_READY         5
#define SYS_SYSTEM_IN_ERROR             6

#define O_STOP                1
#define O_STEADY_STATE        2
#define O_START_TO_STEADY     3


#endif
