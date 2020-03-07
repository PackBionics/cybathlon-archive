#include "LoadCell_functions.h"
#include "Encoder_functions.h"
#include "Motor_functions.h"
#include "FSM.h"
#include "Button.h"
#include "Thresholds.h"
#include "Sensor_Interrupt.h"
#include "Inner_FSMs.h"

//#include "Accelerometer_functions.h"


//#define DEBUG_CONFIG // comment this line out to run full system
//#define CALIBRATION_CONFIG_LC // comment this line out to run full system
//#define CALIBRATION_CONFIG_ENCODER // comment this line out to run full system
//#define EXTEND_LEG // this is used to extend the leg upon startup

void setup() {
  Serial.begin(9600);
  Init_Encoders();
  Init_Interrupt();
  //  Init_Motors();
  //  Init_Button();
  #ifdef DEBUG_CONFIG

  #endif
  
  #ifdef CALIBRATION_CONFIG_LC
    Calibrate_LC(loadcell1);
    Calibrate_LC(loadcell2);
    Calibrate_LC(loadcell3);
    Calibrate_LC(loadcell4);
  #endif

  #ifdef CALIBRATION_CONFIG_ENCODER
    // For calibrating encoders, we need to first
    // make sure that they are initialized at full extension
    // Then we set the encoders to 0
    setZeroSPI(ENC_0);
    setZeroSPI(ENC_1);
  #endif

  #ifdef EXTEND_LEG
    
  #endif

  boolean startDialogue = true;
}

void loop() {
  if (startDialogue) {
    Serial.println("Welcome to the the Stryder Calibration Setup! Select one of the options below to calibrate.");
    Serial.println("1: Absolute Encoder (Knee)");
    Serial.println("2: Absolute Encoder (Cam)");
    Serial.println("3: Load Cells");
    Serial.println("4: Accelerometer");
    startDialogue = false;
  } else {
    if (Serial.available() > 0) {
      int input = Serial.parseInt();
      Serial.read()
      Motor_functions.rot(input);
    }
    Serial.println(encKnee);
  } 
}
