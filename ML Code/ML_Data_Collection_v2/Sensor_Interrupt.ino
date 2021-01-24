#include <TimerOne.h>

/**
 * Initializes Interrupt
 */
void Init_Interrupt() {
  Timer1.initialize(10000);
  Timer1.attachInterrupt(Read_Sensors, 10000);
//  sensorTimer.begin(Read_Sensors, 10000);
}

/**
 * NOTE:
 * 
 *    // to read a variable which the interrupt code writes, we
 *    // must temporarily disable interrupts, to be sure it will
 *    // not change while we are reading.  To minimize the time
 *    // with interrupts off, just quickly make a copy, and then
 *    // use the copy while allowing the interrupt to keep working.
 *    noInterrupts();
 *    blinkCopy = blinkCount;
 *    interrupts();
 * 
 */

/**
 * Function to update sensor global variables
 */
void Read_Sensors() {
  i2c_flag = true;
}

void Update_I2C() {
  encKnee = bitToDegrees(getPositionSPI(ENC_0, RES14));
  
  imu::Vector<3> grav1 = bno1.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  imu::Vector<3> gyro1 = bno1.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  imu::Vector<3> magnet1 = bno1.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
  imu::Vector<3> eul1 = bno1.getVector(Adafruit_BNO055::VECTOR_EULER);
  imu::Vector<3> acc1 = bno1.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  imu::Vector<3> linacc1 = bno1.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  imu::Quaternion quat1 = bno1.getQuat();
  
  double tempX1 = X1_ORIENTATION * grav1.x();
  double tempY1 = Y1_ORIENTATION * grav1.y();
  double tempZ1 = Z1_ORIENTATION * grav1.z();
  if ((tempX1 == 0) && (tempY1 == 0) && (tempZ1 == 0)) {
    Serial.println("IMU1 Froze...Reseting");
//    Rst_Acc();
//    was_fixed = false;
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
    quatW1 = quat1.w();
//    quatX1 = X1_ORIENTATION * quat1.x();
//    quatY1 = Y1_ORIENTATION * quat1.y();
//    quatZ1 = Z1_ORIENTATION * quat1.z();
    quatX1 = quat1.x();
    quatY1 = quat1.y();
    quatZ1 = quat1.z();
  }

  i2c_flag = false;
}
