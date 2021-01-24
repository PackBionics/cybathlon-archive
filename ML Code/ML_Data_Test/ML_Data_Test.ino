#include "KneeAngle_Model.h"

long tic;
long toc;
long time_start;
bool started;
long tot_time;

void setup() {
  Serial.begin(115200);
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
  delay(500);

//// pick up a random x and predict its sine
//    float x_test[64] = { 0.    , 0.    , 0.625 , 0.875 , 0.5   , 0.0625, 0.    , 0.    ,
//                         0.    , 0.125 , 1.    , 0.875 , 0.375 , 0.0625, 0.    , 0.    ,
//                         0.    , 0.    , 0.9375, 0.9375, 0.5   , 0.9375, 0.    , 0.    ,
//                         0.    , 0.    , 0.3125, 1.    , 1.    , 0.625 , 0.    , 0.    ,
//                         0.    , 0.    , 0.75  , 0.9375, 0.9375, 0.75  , 0.    , 0.    ,
//                         0.    , 0.25  , 1.    , 0.375 , 0.25  , 1.    , 0.375 , 0.    ,
//                         0.    , 0.5   , 1.    , 0.625 , 0.5   , 1.    , 0.5   , 0.    ,
//                         0.    , 0.0625, 0.5   , 0.75  , 0.875 , 0.75  , 0.0625, 0.    };
//    float y_pred[10] = {0};
//    int y_test = 8;
//
//    uint32_t start = micros();
//
//    ml.predict(x_test, y_pred);
//
//    uint32_t timeit = micros() - start;
//
//    Serial.print("It took ");
//    Serial.print(timeit);
//    Serial.println(" micros to run inference");
//
//    Serial.print("Test output is: ");
//    Serial.println(y_test);
//    Serial.print("Predicted proba are: ");
//
//    for (int i = 0; i < 10; i++) {
//        Serial.print(y_pred[i]);
//        Serial.print(i == 9 ? '\n' : ',');
//    }
//
//    Serial.print("Predicted class is: ");
//    Serial.println(ml.probaToClass(y_pred));
//    Serial.print("Sanity check: ");
//    Serial.println(ml.predictClass(x_test));
//
//    delay(1000);
}
