#ifndef Accelerometer_functions
#define Accelerometer_functions

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

sensors_event_t event;

Adafruit_MMA8451 mma = Adafruit_MMA8451();


void Init_Accelerometer(void);
int getX(void);
int getY(void);
int getZ(void);
int acc_to_ang(int);

#endif