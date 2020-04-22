void Init_Accelerometer() {
  if (!mma.begin()) {
    Serial.println("Couldnt start");
    while (!mma.begin());
  }  
  if (mma.getRange() != 1) {
    mma.setRange(MMA8451_RANGE_2_G);
  }
}

double getX() {
  mma.getEvent(&event);
  return event.acceleration.x;
}

double getY() {
  mma.getEvent(&event);
  return event.acceleration.y;
}

double getZ() {
  mma.getEvent(&event);
  return event.acceleration.z;
}
