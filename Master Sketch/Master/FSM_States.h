// States in the FSM
enum FSMState {LOCKED, MIDSTANCE, SIT, STAND, GAIT, H_STRIKE, FULL_EXT, RETRACTION};

// global variables
FSMState curr_state = LOCKED; // global variable for keeping track of state in fsm

// FSM Function
void FSM(FSMState init_state);
