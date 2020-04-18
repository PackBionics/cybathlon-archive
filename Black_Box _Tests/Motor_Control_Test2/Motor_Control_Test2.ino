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
#define CALIBRATION_CONFIG_ENCODER // comment this line out to run full system
//#define EXTEND_LEG // this is used to extend the leg upon startup

long tic;
long toc;
int firstPos;
int secondPos;
  
void setup() {
  // Initialize
  Init_Encoders();
  Init_LC();
  Init_Motors();
  //  Init_Button();
  Init_Interrupt();
  Init_Accelerometer();
  Serial.begin(9600);


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
    String s = Serial.readString();
    int s0 = s.indexOf(",");
    String s1 = s.substring(0,s0);
    String s2 = s.substring(s0+1);
    firstPos = s1.toInt();
    secondPos = s2.toInt();
    Serial.print(firstPos);
    Serial.print("\t");
    Serial.println(secondPos);
    rotate(firstPos);
    tic = millis();
  }
  toc = millis();
  if (toc-tic > 500) {
    rotate(secondPos);
  }
//  Serial.print("Knee Encoder: ");
//  Serial.print(encKnee);
//  Serial.print("\t");
//  Serial.print("CAM Encoder: ");
//  Serial.println(encCAM);
}
