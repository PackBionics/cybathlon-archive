#include "LoadCell_functions.h"
#include "Encoder_functions.h"
#include "Motor_functions.h"
#include "FSM.h"
#include "Button.h"
#include "Thresholds.h"
#include "Sensor_Interrupt.h"
#include "Inner_FSMs.h"


#define PWM         9                   //Pin for Power of motor.
#define DIR         10                  //Pin for Direction of the motor.

int vel = 0;

void setup() {
  Serial.begin(9600);
  Init_Encoders();
  Init_Interrupt();
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
  if (Serial.available() > 0) {
    int input = Serial.parseInt();
    Serial.read()
    Motor_functions.rot(input);
  }
  Serial.println(encKnee);
}
