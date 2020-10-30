#include "LoadCell_functions.h"
#include "Encoder_functions.h"
#include "Motor_functions.h"
#include "FSM.h"
#include "Button.h"
#include "Thresholds.h"
#include "Sensor_Interrupt.h"
#include "Inner_FSMs.h"
#include "Accelerometer_functions.h"

long tic;
long toc;
//int new_ang = 110;
//int init_cam = -1000;

//#define DEBUG_CONFIG // comment this line out to run full system
//#define CALIBRATION_CONFIG_LC // comment this line out to run full system
//#define CALIBRATION_CONFIG_ENCODER_KNEE // comment this line out to run full system
//#define CALIBRATION_CONFIG_ENCODER_CAM // comment this line out to run full system
//#define EXTEND_LEG // this is used to extend the leg upon startup

void setup() {
  // Initialize
  Init_Encoders();
  Init_LC();
  Init_Motors();
  Init_Button();
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

#ifdef CALIBRATION_CONFIG_ENCODER_KNEE
  // For calibrating encoders, we need to first
  // make sure that they are initialized at full extension
  // Then we set the encoders to 0
  delayMicroseconds(50000);
  setZeroSPI(ENC_0);
#endif

#ifdef CALIBRATION_CONFIG_ENCODER_CAM
  // For calibrating encoders, we need to first
  // make sure that they are initialized at full extension
  // Then we set the encoders to 0
  delayMicroseconds(50000);
  auto_cal_enc();
#endif

#ifdef EXTEND_LEG

#endif
  delay(1000);
  tic = micros();
  toc = micros();
  delay(3000);

//  new_ang = 0;
}

void loop() {
  if (i2c_flag) {
    Update_I2C();
    tic = micros()-toc;
    toc = micros();
  }
  Serial.print("Time: "); Serial.print(tic); Serial.print("\t");
  Serial.print("Button: "); Serial.print(button_state); Serial.print("\t"); 
  Serial.print("LC: "); Serial.print(lcFront); Serial.print("\t");
  Serial.print(lcBack); Serial.print("\t");  
  Serial.print(lcLeft); Serial.print("\t");
  Serial.print(lcRight); Serial.print("\t");
//  Serial.print("State: "); Serial.print(curr_state); Serial.print("\t"); Serial.print(gait_curr_state); Serial.print("\t");
//  Serial.println();
  Serial.print("Encoder 0: "); Serial.print(encKnee); Serial.print("\t");
  Serial.print("Encoder 1: "); Serial.print(encCAM); Serial.print("\t");
  Serial.print("X: \t"); Serial.print(accX); Serial.print("\t");
  Serial.print("Y: \t"); Serial.print(accY); Serial.print("\t");
  Serial.print("Z: \t"); Serial.print(accZ); Serial.print("\t");
  Serial.print("\t Speed: ");
  Serial.print(curr_speed[0]);
  Serial.print("\t");
  Serial.print(curr_speed[1]);
  Serial.print("\t");
  Serial.print(curr_state);
  Serial.print("\t");
  Serial.print(gait_curr_state);
//  Serial.print("m/s^2 ");
  Serial.println();


//    MasterFSM(curr_state);

//  rotate_helper(115, 0);
//  if (encCAM != init_cam) {
//    Serial.print(encCAM);
//    Serial.print("\t");
//    Serial.print(encKnee);
//    Serial.println(",");
//    init_cam = encCAM;
//  }
//  
//  rotate(70);
//  rotate_helper(40, 0);

//  Serial.print("Knee Angle: ");
//  Serial.print(encKnee);
//  Serial.print("\tCAM Angle: ");
//  Serial.print(encCAM);
//  Serial.print("\tExpected Angle: ");
//  Serial.print(enc_convert());
//  Serial.print("\t Speed: ");
//  Serial.print(curr_speed[0]);
//  Serial.print("\t");
//  Serial.print(curr_speed[1]);
//  Serial.print("\t");
//  Serial.println(curr_dir[0]);
    int new_ang;
    if (encKnee >= 90) {
      new_ang = 0;
    } else if (encKnee <= 5) {
      new_ang = 100;
    }
    rotate_helper(new_ang, 0);

//  if (Serial.available()) {
//    int temp = Serial.parseInt();
//    if (temp != 0) {
//      new_ang = temp;
//    }
//  }
//  rotate_helper(new_ang, 0);

}
