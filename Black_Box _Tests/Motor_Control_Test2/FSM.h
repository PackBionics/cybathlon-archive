// States in the Master FSM
enum MasterFSMState {LOCKED, MIDSTANCE, SIT, STAND, GAIT, H_STRIKE, FULL_EXT, RETRACTION};

// global variables
MasterFSMState curr_state = LOCKED; // global variable for keeping track of state in fsm
boolean fully_retracted = false; // global variable for keeping track of if the leg is fully retracted
boolean fully_extended = true; // global variable for keeping track of if the leg is fully extended
boolean retracted = false; // global variable for keeping track of whether the leg has been retracted recently (reset to false when leg changes out of RETRACTED State)
boolean isGaitComplete = false; // keeps track of whether the entire gait cycle has been completed

// FSM Function
void MasterFSM(MasterFSMState init_state);
