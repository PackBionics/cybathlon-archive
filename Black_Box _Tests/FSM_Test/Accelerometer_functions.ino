void Init_Accelerometer() {
  if (!mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }  
  if (mma.getRange() != 1) {
    mma.setRange(MMA8451_RANGE_2_G);
  }
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
