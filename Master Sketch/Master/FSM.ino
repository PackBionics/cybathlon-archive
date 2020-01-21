// boolean for whether the leg has fully retracted for RETRACTION State
boolean retracted = false;

/**
 * FSM contains the entire FSM of the 
 */
int FSM(FSMState init_state) {
  FSMState current_state = init_state;
  while(1) {
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
        } else if (lcFront < ZERO_ERROR && lcBack < ZERO_ERROR && lcRight < ZERO_ERROR && lcLeft < ZERO_ERROR) {
          current_state = RETRACTION;
        }
        break;
      case SIT:

        break;
      case STAND:

        break;
      case GAIT:

        break;
      case H_STRIKE:

        break;
      case FULL_EXT:

        break;
      case RETRACTION:

        break;
      default:

        break;
    }
  }
  return 0;
}
