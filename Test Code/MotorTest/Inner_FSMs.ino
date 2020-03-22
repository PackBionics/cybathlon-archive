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


void Free_Swing() {
  // Need to figure out how to get g_ang instead of using EXT_ANG and RET_ANG to be able to better control speed through rotate function
  // either use getX and getY or somehow figure out how to use transient rotation from accelerometer
  int g_ang = encKnee + acc_to_ang(getX());
  if (abs(getX() + getY()) > G_TH) {
    if (getY() > G_TH_MAX || getY() < G_TH_MIN) {
      if (getX() < FS_X_TH_NEG) {
        rotate(MTR_FORWARD, g_ang);
      } else {
        rotate(MTR_BACKWARD, g_ang);
      }
    } else {
      analogWrite(PWM, 0);
      curr_speed = 0;
    }
  } else {
    analogWrite(PWM, 0);
    curr_speed = 0;
  }
}

int GaitFSM(GaitFSMState init_state) {
  gait_curr_state = init_state;
  switch(gait_curr_state) {
    case HEEL_OFF:
      // Bend_Knee();
      if (lcFront <= GAIT_HEEL_OFF_SWING_RET_TH ) {
        gait_curr_state = SWING_RET;
      }
      return 1;
    case SWING_RET:
      // Retract_Knee();
      // if (yAcc == ankles_aligned_threshold) {
        gait_curr_state = SWING_EXT;
      return 1;
    case SWING_EXT:
      // Extend_Knee();
      if (lcBack > GAIT_SWING_EXT_END_TH) {
        gait_curr_state = HEEL_OFF; // set it back to the first state for the next run of the Gait FSM
      }
      return 0;
    default:
      return 1;
  }
}

// --------------------------------------------------------------------------------------------------------------

void Bend_Knee() {
  
}

void Retract_Knee() {
  
}

void Extend_Knee() {
  
}
