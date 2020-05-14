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

int s = encKnee;

void setup() {
  // Initialize
  Init_Encoders();
  Init_LC();
  Init_Motors();
  //  Init_Button();
  Init_Interrupt();
//  Init_Accelerometer();
  Serial.begin(115200);

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
  delayMicroseconds(50000);
  setZeroSPI(ENC_0);
  setZeroSPI(ENC_1);
#endif

#ifdef EXTEND_LEG

#endif
  delay(1000);

  // Message Explaining Test Parameters
  Serial.write("This test applies to Black Box Test(s) 1,2,3 and 6 to 11");
  Serial.write("\n");
  Serial.write("The purpose of the test code is to move the leg to a desired angle from a zero degree starting point");
  Serial.write("\n");
  Serial.write("List of test parameter(s) and format: ");
  Serial.write("\n");
  Serial.write("Angle");
  Serial.write("\n");
  Serial.write("Angle: Desired angle to move to (deg)");
  Serial.write("\n");
  Serial.write("Angles are relative about the knee, maximum is ~115 deg and minimum is 0 deg, ex: leg straight is zero degrees");
  Serial.write("\n");
  Serial.write("What You Write In the Serial Monitor Example: ");
  Serial.write("\n");
  Serial.write("60");
  Serial.write("\n");
  Serial.write("The leg initiliazes at zero degrees (full extension) and then moves to 60 degrees");
}

void loop() {
  if (Serial.available() > 0) {
    s = Serial.parseInt();
    Serial.read();
    Serial.println("________________________________________________________________________________");
    Serial.print("Rotating knee to ");
    Serial.print(s);
    Serial.println(" degrees.");
  }
  rotate(s);
  Serial.print("Knee Encoder: ");
  Serial.print(encKnee);
  Serial.print("\t");
  Serial.print("CAM Encoder: ");
  Serial.println(encCAM);
}
