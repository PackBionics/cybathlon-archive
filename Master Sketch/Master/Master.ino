#include "LoadCell.h"
#include "Encoder.h"

//#define DEBUG_CONFIG // comment this line out to run full system
//#define CALIBRATION_CONFIG_LC // comment this line out to run full system
//#define CALIBRATION_CONFIG_ENCODER // comment this line out to run full system
//#define EXTEND_LEG // this is used to extend the leg upon startup


void setup() {
  Init_Encoders();
  Init_LC();

  
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
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("LC: ");
  Serial.print(loadcell1.read()/1000);
  Serial.println();
  Serial.print("Encoder 0: ");
  Serial.print(getPositionSPI(ENC_0, RES14), DEC);
  Serial.println();
  Serial.print("Encoder 1: ");
  Serial.print(getPositionSPI(ENC_1, RES14), DEC);
  Serial.println();
}
