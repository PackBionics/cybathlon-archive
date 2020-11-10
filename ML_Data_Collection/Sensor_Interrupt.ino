#include <TimerOne.h>

/**
 * Initializes Interrupt
 */
void Init_Interrupt() {
  Timer1.initialize(10000);
  Timer1.attachInterrupt(Read_Sensors, 10000);
}

/**
 * Function to update sensor global variables
 */
void Read_Sensors() {
  i2c_flag = true;
}

void Update_I2C() {
  imu::Vector<3> grav1 = bno1.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  imu::Vector<3> gyro1 = bno1.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  imu::Vector<3> magnet1 = bno1.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  imu::Vector<3> eul1 = bno1.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  imu::Vector<3> acc1 = bno1.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  imu::Vector<3> linacc1 = bno1.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  double tempX1 = X1_ORIENTATION * grav1.x();
  double tempY1 = Y1_ORIENTATION * grav1.y();
  double tempZ1 = Z1_ORIENTATION * grav1.z();
  if ((tempX1 == 0) && (tempY1 == 0) && (tempZ1 == 0)) {
    Serial.println("IMU1 Froze...Reseting");
    Rst_Acc();
    was_fixed = false;
  } else {
    gravX1 = tempX1;
    gravY1 = tempY1;
    gravZ1 = tempZ1;
    gyroX1 = X1_ORIENTATION * gyro1.x();
    gyroY1 = Y1_ORIENTATION * gyro1.y();
    gyroZ1 = Z1_ORIENTATION * gyro1.z();
    magnetX1 = X1_ORIENTATION * magnet1.x();
    magnetY1 = Y1_ORIENTATION * magnet1.y();
    magnetZ1 = Z1_ORIENTATION * magnet1.z();
    eulX1 = X1_ORIENTATION * eul1.x();
    eulY1 = Y1_ORIENTATION * eul1.y();
    eulZ1 = Z1_ORIENTATION * eul1.z();
    accX1 = X1_ORIENTATION * acc1.x();
    accY1 = Y1_ORIENTATION * acc1.y();
    accZ1 = Z1_ORIENTATION * acc1.z();
    linaccX1 = X1_ORIENTATION * linacc1.x();
    linaccY1 = Y1_ORIENTATION * linacc1.y();
    linaccZ1 = Z1_ORIENTATION * linacc1.z();
  }  

  imu::Vector<3> grav2 = bno2.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  imu::Vector<3> gyro2 = bno1.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  imu::Vector<3> magnet2 = bno1.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  imu::Vector<3> eul2 = bno1.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  imu::Vector<3> acc2 = bno1.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  imu::Vector<3> linacc2 = bno1.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  double tempX2 = Y2_ORIENTATION * grav2.y();
  double tempY2 = X2_ORIENTATION * grav2.x();
  double tempZ2 = Z2_ORIENTATION * grav2.z();
  if ((tempX2 == 0) && (tempY2 == 0) && (tempZ2 == 0)) {
    Serial.println("IMU2 Froze...Reseting");
    Rst_Acc();
    was_fixed = false;
  } else {
    gravX2 = tempX2;
    gravY2 = tempY2;
    gravZ2 = tempZ2;
    gyroX2 = Y2_ORIENTATION * gyro2.y();
    gyroY2 = X2_ORIENTATION * gyro2.x();
    gyroZ2 = Z2_ORIENTATION * gyro2.z();
    magnetX2 = Y2_ORIENTATION * magnet2.y();
    magnetY2 = X2_ORIENTATION* magnet2.x();
    magnetZ2 = Z2_ORIENTATION * magnet2.z();
    eulX2 = Y2_ORIENTATION * eul2.y();
    eulY2 = X2_ORIENTATION * eul2.x();
    eulZ2 = Z2_ORIENTATION * eul2.z();
    accX2 = Y2_ORIENTATION * acc2.y();
    accY2 = X2_ORIENTATION * acc2.x();
    accZ2 = Z2_ORIENTATION * acc2.z();
    linaccX2 = Y2_ORIENTATION * linacc2.y();
    linaccY2 = X2_ORIENTATION * linacc2.x();
    linaccZ2 = Z2_ORIENTATION * linacc2.z();
  }  

  i2c_flag = false;
}
