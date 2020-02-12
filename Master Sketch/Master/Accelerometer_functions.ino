void Init_Accelerometer() {
  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }  
  if (mma.getRange() != 1) {
    mma.setRange(MMA8451_RANGE_2_G);
  }
}

int getX() {
  mma.getEvent(&event);
  return event.acceleration.x;
}

int getY() {
  mma.getEvent(&event);
  return event.acceleration.y;
}

int getZ() {
  mma.getEvent(&event);
  return event.acceleration.z;
}
