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
  int input = 0;
  
}

void loop() {
  if (startDialogue) {
    Serial.println("Welcome to the the Stryder Calibration Setup! Select one of the options below to calibrate.");
    Serial.println("1: Absolute Encoders");
    Serial.println("2: Load Cells");
    Serial.println("3: Accelerometer");
    startDialogue = false;
    int kneeDialogue = true;
  } else {
    if (Serial.available() > 0) {
      input = Serial.parseInt();
      Serial.read();
      if (input < 0 || input > 4) {
        Serial.println("Not A Valid Option.");
      }
    }
    switch (input) {
        case 1:
          if (kneeDialogue) {
            Serial.println("Please Lock Knee at Full Leg Extension. Type ""L"" when knee is locked.");
            kneeDialogue = false;
          } else {
            if (Serial.available() > 0) {
              char in = Serial.read()
              if (in == 'L') {
                int knee180 = encKnee;
                int cam180 = encCam;
                
              }
            }
          }
          break;
        case 2:

          break;
        case 3:

          break;
      }
  } 
}
