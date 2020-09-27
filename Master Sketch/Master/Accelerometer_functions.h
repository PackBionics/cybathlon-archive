#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

sensors_event_t event;

Adafruit_MMA8451 mma = Adafruit_MMA8451();

double accX;
double accY;
double accZ;
double gravAcc = 9.81;

void Init_Accelerometer(void);
double getX(void);
double getY(void);
double getZ(void);
