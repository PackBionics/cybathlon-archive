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
          
        }
        break;
      case MIDSTANCE:

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
