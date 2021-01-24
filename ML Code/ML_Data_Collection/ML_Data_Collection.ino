#include "Accelerometer_functions.h"
#include "Sensor_Interrupt.h"
#include "KneeAngle_Model.h"

long tic;
long toc;
long time_start;
bool started;
long tot_time;

void setup() {
  Serial.begin(9600);
//  Init_Interrupt();
//  Init_Accelerometer();
  Model_Init();

  delay(1000);
  tic = micros();
  toc = micros();
  started = false;
  delay(3000);
}

void loop() {
//  if (i2c_flag) {
//    Update_I2C();
////    tic = micros()-toc;
////    toc = micros();
//  }
//
//  if (!started) {
//    // We prompt for G - but never check for it
//    Serial.println("Press G and Enter to finish Calibration");
//    while(Serial.available() < 1);
//    // now we clear the serial buffer.
//    while(Serial.available() > 0) {
//      byte dummyread = Serial.read();
//    }
//    time_start = micros();
//    tot_time = 0;
//    started = true;
//  }
//  tic = micros()-toc;
//  toc = micros();
//  tot_time = toc - time_start;
//  if (tot_time <= 60000000) {
//    Serial.print("Time: \t"); Serial.print(tot_time); Serial.print("\t"); Serial.print(tic); Serial.print("\t"); 
//    display_all_sensors();
////    display_quats();
////    display_eul();
//    Serial.println();
//  }
  Predict_Knee_Angle(input_arr_test);
}
