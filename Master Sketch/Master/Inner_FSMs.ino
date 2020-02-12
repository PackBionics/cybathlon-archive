/**
 * Function to monitor speed of Stand to Sit motion
 */
void Sit() {
  if (getX() > SIT_X_TH_POS) {
    curr_speed++;
    rotate(MTR_BACKWARD, RET_ANG);
  } else if (getX() < SIT_X_TH_NEG) {
    curr_speed--;
    rotate(MTR_BACKWARD, RET_ANG);
  }
}

/**
 * Function to monitor speed of Sit to Stand motion
 */
void Stand() {
    if (getX() > STAND_X_TH_POS) {
    curr_speed++;
    rotate(MTR_FORWARD, EXT_ANG);
  } else if (getX() < STAND_X_TH_NEG) {
    curr_speed--;
    rotate(MTR_FORWARD, EXT_ANG);
  }
}
