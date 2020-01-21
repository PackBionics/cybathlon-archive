#define MIDSTANCE_SIT_TH 400 // threshold for determining to go from MIDSTANCE to SIT State (uses heel loading)
#define MIDSTANCE_GAIT_TH 400 // threshold for determining MIDSTANCE to GAIT State (uses toe loading)
#define ZERO_ERROR 50 // error for how close to 0 LCs are to be deemed "0" force

// States in the FSM
enum FSMState {LOCKED, MIDSTANCE, SIT, STAND, GAIT, H_STRIKE, FULL_EXT, RETRACTION};

// FSM Function
int FSM(FSMState init_state);
