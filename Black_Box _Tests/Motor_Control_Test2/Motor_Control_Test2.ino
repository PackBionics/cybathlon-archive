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

//#define DEBUG_CONFIG // comment this line out to run full system
//#define CALIBRATION_CONFIG_LC // comment this line out to run full system
#define CALIBRATION_CONFIG_ENCODER // comment this line out to run full system
//#define EXTEND_LEG // this is used to extend the leg upon startup

long tic;
long toc;
int startingPos;
int firstPos;
int triggerAngle;
int secondPos;
boolean startTest;

char seps[] = ",";
char *token;
int var;
int input[4];
  
void setup() {
  // Initialize
  Init_Encoders();
  Init_LC();
  Init_Motors();
  //  Init_Button();
  Init_Interrupt();
  Init_Accelerometer();
  Serial.begin(9600);
  startTest = false;


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
  // input order: starting position, first position, trigger angle, second position
  if (Serial.available() > 0) {
    String s = Serial.readString();
    token = strtok(s, seps);
    for (int i = 0; i < 4; i++) {
      sscanf(token, "%d", &var);
      input[i] = var;
      token = strtok(NULL, seps);
    }
    startPos = input[0];
    firstPos = input[1];
    triggerAngle = input[2];
    secondPos = input[3];
    startTest = true;
    tic = millis();
  }
  if (startTest) {
    rotate(startPos);
    toc = millis();
    if (toc-tic > 1000) {
      rotate(firstPos);
    }
    if (toc-tic > 1000 && encKnee == triggerAngle) {
      rotate(secondPos);
      startTest = false;
    }
  }
//  if (Serial.available() > 0) {
//    String s = Serial.readString();
//    int s0 = s.indexOf(",");
//    String s1 = s.substring(0,s0);
//    String s2 = s.substring(s0+1);
//    firstPos = s1.toInt();
//    secondPos = s2.toInt();
//    Serial.print(firstPos);
//    Serial.print("\t");
//    Serial.println(secondPos);
//    rotate(firstPos);
//    tic = millis();
//  }
//  toc = millis();
//  if (toc-tic > 500) {
//    rotate(secondPos);
//  }
//  Serial.print("Knee Encoder: ");
//  Serial.print(encKnee);
//  Serial.print("\t");
//  Serial.print("CAM Encoder: ");
//  Serial.println(encCAM);
}
