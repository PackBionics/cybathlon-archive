#include "LoadCell_functions.h"
#include "Encoder_functions.h"
#include "Motor_functions.h"
#include "FSM.h"
#include "Button.h"
#include "Thresholds.h"
#include "Sensor_Interrupt.h"
#include "Inner_FSMs.h"
#include "Accelerometer_functions.h"


//#define DEBUG_CONFIG // comment this line out to run full system
//#define CALIBRATION_CONFIG_LC // comment this line out to run full system
//#define CALIBRATION_CONFIG_ENCODER // comment this line out to run full system
//#define EXTEND_LEG // this is used to extend the leg upon startup


void setup() {
    // Initialize
    Init_Encoders();
    Init_LC();
    Init_Motors();
//  Init_Button();
    Init_Interrupt();
    Init_Accelerometer();

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
//  Serial.print("LC: ");
//  Serial.print(loadcell1.read()/1000);
//  Serial.println();
//  Serial.print("Encoder 0: ");
//  Serial.print(getPositionSPI(ENC_0, RES14), DEC);
//  Serial.println();
//  Serial.print("Encoder 1: ");
//  Serial.print(getPositionSPI(ENC_1, RES14), DEC);
//  Serial.println();
//  MasterFSM(curr_state);
    Serial.println(encKnee);
//    rot(100);
    Serial.println(curr_speed);
}
