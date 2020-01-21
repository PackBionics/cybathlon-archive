// boolean for whether the leg has fully retracted for RETRACTION State
boolean retracted = false;

/**
 * FSM contains the entire FSM of the 
 */
int FSM(FSMState init_state) {
  FSMState state = init_state;
  while(1) {
    switch(state) {
      case LOCKED:

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
