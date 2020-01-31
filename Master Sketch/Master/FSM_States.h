// States in the FSM
enum FSMState {LOCKED, MIDSTANCE, SIT, STAND, GAIT, H_STRIKE, FULL_EXT, RETRACTION};

// FSM Function
void FSM(FSMState init_state);

FSMState curr_state = LOCKED;
