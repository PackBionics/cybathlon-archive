void Init_Accelerometer() {
  if (!mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }  
  if (mma.getRange() != 1) {
    mma.setRange(MMA8451_RANGE_2_G);
  }

//  /* Initialise the sensor */
//  if(!bno.begin())
//  {
//    /* There was a problem detecting the BNO055 ... check your connections */
//    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
//    while(1);
//  }
//  
//  delay(1000);
//    
//  bno.setExtCrystalUse(true);
}

double getX() {
  return event.acceleration.x;
}

double getY() {
  return event.acceleration.y;
}

double getZ() {
  return event.acceleration.z;
}
