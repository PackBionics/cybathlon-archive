// boolean for whether the leg has fully retracted for RETRACTION State
boolean retracted = false;

/**
 * v1.0 of FSM Created on 01/21/20
 * FSM contains the entire FSM of the Leg
 * @param init_state - the initial state that the FSM starts in; should be LOCKED
 * @return exit code - should only happen if fails (returns a 0 in this case)
 */
int FSM(FSMState init_state) {
  FSMState current_state = init_state;
  while(1) { // consider moving while to master sketch (need to make global state variable and return value as FSMState)
    switch(current_state) {
      case LOCKED:
        if (button_state == 0) {
          current_state = MIDSTANCE;
        }
        break;
      case MIDSTANCE:
        if (button_state == 1) {
          current_state = LOCKED;
        } else if (lcBack > MIDSTANCE_SIT_TH) {
          current_state = SIT;
        } else if (lcFront > MIDSTANCE_GAIT_TH) {
          current_state = GAIT;
        } else if (lcFront < ZERO_ERROR_LC && lcBack < ZERO_ERROR_LC && lcRight < ZERO_ERROR_LC && lcLeft < ZERO_ERROR_LC) {
          current_state = RETRACTION;
        }
        break;
      case SIT:
        if (lcBack > SIT_STAND_TH) {
          current_state = STAND;
        } else {
          // Sit();
        }
        break;
      case STAND:
        if ((encKnee +  ENC_MAX / 2) % ENC_MAX - ENC_MAX / 2 < ZERO_ERROR_ENC && abs(lcFront - lcBack) < ZERO_ERROR_LC) {
          current_state = MIDSTANCE;
        } else {
          // Stand();
        }
        break;
      case GAIT:
        if (lcBack > GAIT_H_STRIKE_TH) {
          current_state = H_STRIKE;
        } else {
          // Gait_Motion();
        }
        break;
      case H_STRIKE:
        if ((encKnee +  ENC_MAX / 2) % ENC_MAX - ENC_MAX / 2 < ZERO_ERROR_ENC && abs(lcFront - lcBack) < ZERO_ERROR_LC) {
          current_state = MIDSTANCE;
        } else {
          // Straighten_Leg();
        }
        break;
      case FULL_EXT:
        if ((encKnee +  ENC_MAX / 2) % ENC_MAX - ENC_MAX / 2 < ZERO_ERROR_ENC && abs(lcFront - lcBack) < ZERO_ERROR_LC) {
          current_state = MIDSTANCE;
        }
        break;
      case RETRACTION:
        if (!retracted) {
          // Retract();
          retracted = true;
        }
        if (lcFront > RETRACTION_FULL_EXT_LCFRONT_TH && lcBack > RETRACTION_FULL_EXT_LCBACK_TH
              && lcLeft > RETRACTION_FULL_EXT_LCLEFT_TH && lcRight > RETRACTION_FULL_EXT_LCRIGHT_TH) {
          current_state = FULL_EXT;
          retracted = false;
        } else if (lcBack > RETRACTION_H_STRIKE_LCBACK_TH && lcBack - lcFront > RETRACTION_H_STRIKE_LCBACKFRONT_TH
              && (encKnee +  ENC_MAX / 2) % ENC_MAX - ENC_MAX / 2 < ZERO_ERROR_ENC) {
          current_state = H_STRIKE;
          retracted = false;
        }
        // Free_Swing();
        break;
      default:
        // Do Nothing here
        break;
    }
  }
  return 0;
}
