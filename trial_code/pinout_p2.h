/*
 * PinOut
 * With comments on changes from older one.
 */

//Control Pots
#define TIDAL_VOLUME_PIN    A0 		//Unchanged
#define RR_PIN              A1		//Unchanged
#define PMAX_PIN            A2		//Unchanged
#define FiO2_PIN            A3		//Unchanged
#define POT_5_PIN			A4		// New
#define POT_6_PIN			A5		// New	


//I2C  
#define I2C_SCL_PIN         D21		//Unchanged
#define I2C_SDA_PIN         D20		// Unchanged

//Display
#define DISPLAY_1_PIN       D29		// Changed
#define DISPLAY_2_PIN       D28		// Changed
#define DISPLAY_3_PIN       D27		// Changed
#define DISPLAY_4_PIN       D26		// Changed
#define DISPLAY_ENC_SEL		D25		// Changed

//Motor

#define ARM_DIR_PIN_PIN      D5		// Unchanged
#define ARM_STEP_PIN_PIN     D4 	// Unchanged
#define MOTOR_ARM_ZERO_PIN  D37		// Changed
#define MOTOR_ARM_END_PIN   D36		// Changed

// Valves
#define INPUT_O2_VALVE_PIN   D50	// Changed		
#define PAT_EXHALE_VLV_PIN   D51	// Changed
#define PAT_INHALE_VLV_PIN   D52	// Changed
#define INPUT_AIR_VALVE      D53    // Changed

// Serial
#define TX_PIN               D1		// Unchanged
#define RX_PIN               D0		// Unchanged 


//Sensors::: TBD :: To be confirmed by Madhav T.
#define PATIENT_PR_PIN      A6		// Unspecified
#define PATIENT_O2_PIN      A7		// Unspecified
#define INPUT_O2_PR_PIN     A8		// Unspecified
#define INPUT_AIR_PR_PIN    A9      // Unspecified
#define PUMP_START_STOP_PIN  D9		// Unspecified
#define ARM_CONTROL1_PIN     D7			// Unused
#define ARM_CONTROL2_PIN     D6			// Unused
