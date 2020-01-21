// States in the FSM
enum FSMState {LOCKED, MIDSTANCE, SIT, STAND, GAIT, H_STRIKE, FULL_EXT, RETRACTION};

// FSM Function
int FSM(FSMState init_state);
