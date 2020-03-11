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
long positions[2] = {0, 0};
double spe = 0;
unsigned long tic;
unsigned long toc;

void printDouble( double val, unsigned int precision){
// prints val with number of decimal places determine by precision
// NOTE: precision is 1 followed by the number of zeros for the desired number of decimial places
// example: printDouble( 3.1415, 100); // prints 3.14 (two decimal places)

   Serial.print (int(val));  //prints the int part
   Serial.print("."); // print the decimal point
   unsigned int frac;
   if(val >= 0)
       frac = (val - int(val)) * precision;
   else
       frac = (int(val)- val ) * precision;
   Serial.println(frac,DEC) ;
}

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

  tic = micros();
  toc = micros();
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
  toc = micros();
  unsigned long dTime = toc - tic;
  if (dTime > 100000) {
    tic = micros();
    positions[0] = positions[1];
    positions[1] = (double) encKnee;
    spe = (double)((double) bitToDegrees(abs(positions[1] - positions[0])))/((double)(100.0 * abs((double) dTime)/1000000.0));
    printDouble(spe, 100);
  }
}
