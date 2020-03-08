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

  #ifdef EXTEND_LEG
    
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

  boolean startDialogue = true;
  int input = 0;
  boolean dialogue1 = true;
}

void loop() {
  if (startDialogue) {
    Serial.println("Welcome to the the Stryder Diagnostic Protocol! Select one of the options below to diagnose.");
    Serial.println("1: Motor and Absolute Encoders");
    Serial.println("2: Load Cells");
    Serial.println("3: Accelerometer");
    Serial.println("4: Lock Button");
    startDialogue = false;
    dialogue1 = true;
  } else {
    if (Serial.available() > 0) {
      input = Serial.parseInt();
      Serial.read();
      if (input < 1 || input > 4) {
        Serial.println("Not A Valid Option.");
      }
    }
    switch (input) {
        case 1:
          if (dialogue1) {
            Serial.println("Please type in desired knee angle. Type ""Q"" to quit Motor and Absolute Encoders Diagnosis.");
            dialogue1 = false;
          } else {
            if (Serial.available() > 0) {
              String input = Serial.readString();
              if (input.equals("Q")) {
                startDialogue = true;
                input = 0;
                Serial.println("Quiting");
              } else if (isDigit(input.charAt(0))) {
                int angle = input.toInt();
                Serial.println("Input Knee Angle (degrees): " + angle);
                Motor_functions.rot(angle);
                delay(1000);
                Serial.println("Knee Encoder Reading: " + encKnee + " degrees");
                Serial.println("Cam Encoder Reading: " + encCam + " degrees");                
              } else {
                Serial.println("Invalid Angle");
              }
            }
          }
          break;
          
        case 2:

          break;
          
        case 3:

          break;
          
        case 4:

          break;
      }
  } 
}
