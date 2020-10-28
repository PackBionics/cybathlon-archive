//#include <Wire.h>
//#include <Adafruit_MMA8451.h>
//#include <Adafruit_Sensor.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//sensors_event_t event;

#define RESET_PIN 23

//Adafruit_MMA8451 mma = Adafruit_MMA8451();
Adafruit_BNO055 bno = Adafruit_BNO055();

double accX;
double accY;
double accZ;
double gravAcc = 9.81;
bool was_fixed = true;

void Init_Accelerometer(void);
void Rst_Acc(void);
//double getX(void);
//double getY(void);
//double getZ(void);
