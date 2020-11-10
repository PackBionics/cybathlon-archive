#include "Accelerometer_functions.h"
#include "Sensor_Interrupt.h"

long tic;
long toc;
long time_start;
bool started;
long tot_time;

void setup() {
  Init_Interrupt();
  Init_Accelerometer();

  delay(1000);
  tic = micros();
  toc = micros();
  started = false;
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
  if (tot_time <= 60000000) {
    Serial.print("Time: \t"); Serial.print(tot_time); Serial.print("\t"); Serial.print(tic); Serial.print("\t"); 
    
    Serial.print("Grav1: \t"); Serial.print(gravX1); Serial.print("\t"); Serial.print(gravY1); Serial.print("\t"); Serial.print(gravZ1); Serial.print("\t");
    Serial.print("Gyro1: \t"); Serial.print(gyroX1); Serial.print("\t"); Serial.print(gyroY1); Serial.print("\t"); Serial.print(gyroZ1); Serial.print("\t");
    Serial.print("Magnet1: \t"); Serial.print(magnetX1); Serial.print("\t"); Serial.print(magnetY1); Serial.print("\t"); Serial.print(magnetZ1); Serial.print("\t");
    Serial.print("Euler1: \t"); Serial.print(eulX1); Serial.print("\t"); Serial.print(eulY1); Serial.print("\t"); Serial.print(eulZ1); Serial.print("\t");
    Serial.print("Acc1: \t"); Serial.print(accX1); Serial.print("\t"); Serial.print(accY1); Serial.print("\t"); Serial.print(accZ1); Serial.print("\t");
    Serial.print("LinAcc1: \t"); Serial.print(linaccX1); Serial.print("\t"); Serial.print(linaccY1); Serial.print("\t"); Serial.print(linaccZ1); Serial.print("\t");
  
    
    Serial.print("Grav2: \t"); Serial.print(gravX2); Serial.print("\t"); Serial.print(gravY2); Serial.print("\t"); Serial.print(gravZ2); Serial.print("\t");
    Serial.print("Gyro2: \t"); Serial.print(gyroX2); Serial.print("\t"); Serial.print(gyroY2); Serial.print("\t"); Serial.print(gyroZ2); Serial.print("\t");
    Serial.print("Magnet2: \t"); Serial.print(magnetX2); Serial.print("\t"); Serial.print(magnetY2); Serial.print("\t"); Serial.print(magnetZ2); Serial.print("\t");
    Serial.print("Euler2: \t"); Serial.print(eulX2); Serial.print("\t"); Serial.print(eulY2); Serial.print("\t"); Serial.print(eulZ2); Serial.print("\t");
    Serial.print("Acc2: \t"); Serial.print(accX2); Serial.print("\t"); Serial.print(accY2); Serial.print("\t"); Serial.print(accZ2); Serial.print("\t");
    Serial.print("LinAcc2: \t"); Serial.print(linaccX2); Serial.print("\t"); Serial.print(linaccY2); Serial.print("\t"); Serial.print(linaccZ2); Serial.print("\t");
    Serial.println();
  }
}
