#include "Accelerometer_functions.h"
#include "Sensor_Interrupt.h"
#include "Encoder_functions.h"

#define TIME_TRIAL 60 // how long the data trial is (seconds)
#define TIME_TEST 10 // how long the data trial is for initialize testing (seconds)

long tic;
long toc;
long time_start;
bool started;
long tot_time;
long trial_time;

#define CALIBRATION_CONFIG_ENCODER_KNEE // comment this line out to run full system

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Initializing Interrupt");
  Init_Interrupt();
  Serial.println("Initializing Encoder");
  Init_Encoders();

#ifdef CALIBRATION_CONFIG_ENCODER_KNEE
  // For calibrating encoders, we need to first
  // make sure that they are initialized at full extension
  // Then we set the encoders to 0
  Serial.println("Zeroing Encoder");
  delayMicroseconds(50000);
  setZeroSPI(ENC_0);
#endif

  Serial.println("Initializing Accelerometer");
  Init_Accelerometer();
  Serial.println("Done Initializing");

  delay(1000);
  tic = micros();
  toc = micros();
  started = false;
  trial_time = TIME_TEST * 1000000;
  delay(3000);
}

void loop() {
  if (i2c_flag) {
    Update_I2C();
//    tic = micros()-toc;
//    toc = micros();
  }

  if (!started) {
    // We prompt for G - but never check for it
    Serial.println("Press G and Enter to finish Calibration");
    while(Serial.available() < 1);
    // now we clear the serial buffer.
    while(Serial.available() > 0) {
      byte dummyread = Serial.read();
    }
    time_start = micros();
    tot_time = 0;
    started = true;
  }
  tic = micros()-toc;
  toc = micros();
  tot_time = toc - time_start;
  if (tot_time <= trial_time) {
    Serial.print("Time: \t"); Serial.print(tot_time); Serial.print("\t"); Serial.print(tic); Serial.print("\t"); 
    Serial.print("\tAngle:\t"); Serial.print(encKnee); Serial.print("\t");
    display_all_sensors();
//    display_quats();
//    display_eul();
    Serial.println();
  } else {
    started = false;
    trial_time = TIME_TRIAL * 1000000;
  }
}
