void Init_Accelerometer() {
  if (!mma.begin()) {
    Serial.println("Couldnt start");
    while (!mma.begin());
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

/**
 * converts given acceleration to an angle that can be
 * used for calculating angle direction for gravity
 */
int acc_to_ang(int acc) {
  return 0;
}
