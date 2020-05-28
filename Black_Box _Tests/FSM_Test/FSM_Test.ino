#include "LoadCell_functions.h"
#include "Encoder_functions.h"
#include "Motor_functions.h"
#include "FSM.h"
#include "Button.h"
#include "Thresholds.h"
#include "Sensor_Interrupt.h"
#include "Inner_FSMs.h"
#include "Accelerometer_functions.h"

#include <string.h>
#include <stdio.h>

char seps[] = "=";
char *token;
int var;
int input[2];
char s[100];
char *token2;


//#define DEBUG_CONFIG // comment this line out to run full system
//#define CALIBRATION_CONFIG_LC // comment this line out to run full system
//#define CALIBRATION_CONFIG_ENCODER // comment this line out to run full system
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
}

void loop() {
//  if (i2c_flag) { ## this kills the sensors
//    Update_I2C();
//  }
//  Serial.print("LC: "); Serial.print(lcFront); Serial.print("\t");
//  Serial.print("Encoder 0: "); Serial.print(encKnee); Serial.print("\t");
//  Serial.print("Encoder 1: "); Serial.print(encCAM); Serial.print("\t");
//  Serial.print("X: \t"); Serial.print(accX); Serial.print("\t");
//  Serial.print("Y: \t"); Serial.print(accY); Serial.print("\t");
//  Serial.print("Z: \t"); Serial.print(accZ); Serial.print("\t");
//  Serial.println("m/s^2 ");


  if (Serial.available() > 0) {
    String string = Serial.readString();
    string.toCharArray(s, 100);
    token = strtok(s, seps);
    token2 = strtok(NULL, seps);
    sscanf(token2, "%d", &var);

    if (strcmp(token, "lcBack")) {
      lcBack = var;
    } else if (strcmp(token, "lcFront")) {
      lcFront = var;
    } else if (strcmp(token, "lcLeft")) {
      lcLeft = var;
    } else if (strcmp(token, "lcRight")) {
      lcRight = var;
    } else if (strcmp(token, "button_state")) {
      button_state = var;
    } else if (strcmp(token, "encKnee")) {
      encKnee = var;
    } else if (strcmp(token, "encCAM")) {
      encCAM = var;
    } else if (strcmp(token, "accX")) {
      accX = var;
    } else if (strcmp(token, "accY")) {
      accY = var;
    } else if (strcmp(token, "accZ")) {
      accZ = var;
    } else if (strcmp(token, "reset")) { //May need to input reset= to serial monitor b/c of parsing
      accZ = 0;
      accY = -9.81;
      accX = 0;
      encCAM = 0;
      encKnee = 0;
      lcRight = 300;
      lcLeft = 300;
      lcBack = 300;
      lcFront = 300;
    }
    Serial.print("The current state is: ");
    Serial.println(curr_state);
    Serial.print("lcFront = ");
    Serial.println(lcFront);
    Serial.print("lcBack = ");
    Serial.println(lcBack);
    Serial.print("lcLeft = ");
    Serial.println(lcLeft);
    Serial.print("lcRight = ");
    Serial.println(lcRight);
    Serial.print("encKnee = ");
    Serial.println(encKnee);
//    Serial.print("encCAM = ");
//    Serial.println(encCAM);
    Serial.print("accX = ");
    Serial.println(accX);
    Serial.print("accY = ");
    Serial.println(accY);
    Serial.print("accZ = ");
    Serial.println(accZ);
    Serial.print("button_state = ");
    Serial.println(button_state);
    Serial.println("______________________________________________________");
    
  }
 


  //  MasterFSM(curr_state);
  //    Serial.println(encKnee);
  //    rot(100);
  //    Serial.println(curr_speed);
  //  Serial.print("Knee Angle: ");
  //  Serial.print(encKnee);
  //  Serial.print("\t Speed: ");
  //  Serial.println(curr_speed);
  //  int new_ang;
  //  if (encKnee >= 90) {
  //    new_ang = 20;
  //  } else if (encKnee <= 30) {
  //    new_ang = 110;
  //  }
  //  rotate(new_ang);


}
