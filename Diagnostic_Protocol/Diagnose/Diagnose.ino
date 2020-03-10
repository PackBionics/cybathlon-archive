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
    Serial.println("2: Accelerometer");
    Serial.println("3: Load Cells");
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
            Serial.println("Please type in desired knee angle. Type Q to quit Motor and Absolute Encoders Diagnosis.");
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
          if (dialogue1) {
            Serial.println("Type Q to quit Accelerometer Diagnosis.");
            Serial.println("Please specify which axis you are testing.");
            Serial.println("Y : Leg is straight up and down.");
            Serial.println("X : Leg is straight out infront");
            Serial.println("Z : Leg is straight out to the side.");
            dialogue1 = false;
          } else {
            if (Serial.available() > 0) {
              String input = Serial.readString();
              if (input.equals("Q")) {
                startDialogue = true;
                input = 0;
                Serial.println("Quiting");
              } else if (input.equals("Y")) {
                Serial.println("Accelerometer Reading: " + getY() + " G's");                
              } else if (input.equals("X")) {
                Serial.println("Accelerometer Reading: " + getX() + " G's"); 
              } else if (input.equals("Z")) {
                Serial.println("Accelerometer Reading: " + getZ() + " G's"); 
              } else {
                Serial.println("Invalid Input");
              }
            }
          }
          break;
          
        case 3:
          Serial.println("Front: " + lcFront + "N Back: " + lcBack + "N Left: " + lcLeft + "N Right: " + lcRight + "N");
          break;
          
        case 4:
          Serial.println("Begin with the leg unlocked");
          delay(2000);
          if (button_state() > 0) {
            Serial.println("Please unlock leg");
          } else {
            Serial.println("Now lock the leg");
            if (button_state() > 0) {
              Serial.println("Button is pushed");
            } else {
              Serial.println("");
            }
          }
          break;
      }
  } 
}
