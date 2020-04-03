#include "LoadCell_functions.h"
#include "Encoder_functions.h"
#include "Motor_functions.h"
#include "FSM.h"
#include "Button.h"
#include "Thresholds.h"
#include "Sensor_Interrupt.h"
#include "Inner_FSMs.h"
#define PWM         11                 //Pin for Power of motor.
#define DIR         12                  //Pin for Direction of the motor.

int vel = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PWM, OUTPUT);
  pinMode(DIR, OUTPUT);  

    // Initialize
  Init_Encoders();
//  Init_LC();
//  Init_Motors();
//  Init_Button();
  Init_Interrupt();
  
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

}

void loop() {
  if (Serial.available() > 0) {
    int vel = Serial.parseInt();
    Serial.read();
    if (vel < 0) {
      digitalWrite(DIR, LOW);
      analogWrite(PWM, abs(vel));
    } else {
      digitalWrite(DIR, HIGH);
      analogWrite(PWM, abs(vel));
    }
    
  }
  if (encKnee < 3237) {
    vel = 0;
    digitalWrite(DIR, HIGH);
    analogWrite(PWM, abs(vel));
  } else if (encKnee > 8475) {
    vel = 0;
    digitalWrite(DIR, HIGH);
    analogWrite(PWM, abs(vel));
  }
  Serial.print("Knee: ");
  Serial.print(encKnee);
  Serial.print(", CAM: ");
  Serial.println(encCAM);
}
