/*
 * PinOut
 */

//Control Pots
#define TIDAL_VOLUME_PIN    A0 
#define RR_PIN              A1
#define PMAX_PIN            A2
#define FiO2_PIN            A3

//Sensors
#define PATIENT_O2_PIN      A4 
#define PATIENT_PR_PIN      A5
#define MOTOR_ARM_ZERO_PIN  A6
#define INPUT_O2_PR_PIN     A7
#define INPUT_AIR_PR_PIN    A8        // This is MEGA only not present on Uno
  

// ACTUATORS
#define I2C_SCL_PIN         21
#define I2C_SDA_PIN         20

//Display
#define DISPLAY_1_PIN       D13
#define DISPLAY_2_PIN       D12
#define DISPLAY_3_PIN       D11
#define DISPLAY_4_PIN       D10

//Motor
#define PUMP_START_STOP_PIN  D9
#define INPUT_O2_VALVE_PIN   D8
#define ARM_CONTROL1_PIN     D7
#define ARM_CONTROL2_PIN     D6
#define ARM_DIR_PIN_PIN      D5
#define ARM_STEP_PIN_PIN     D4 
#define PAT_EXHALE_VLV_PIN   D3
#define PAT_INHALE_VLV_PIN   D2
#define TX_PIN               D1
#define RX_PIN               D0

#define INPUT_AIR_VALVE     D14   // This is MEGA only not present on Uno

