#ifndef Inner_FSMs
#define Inner_FSMs

// States in the Gait FSM
enum GaitFSMState {HEEL_OFF, SWING_RET, SWING_EXT, END};

// global variables
GaitFSMState gait_curr_state = HEEL_OFF;

// Function that monitors speed of standing to sitting motion
void Sit(void);
// Function that monitors speed of sitting to standing motion
void Stand(void);
// Function that tries to mimic "free swing" by finding the "angle" of gravity
void Free_Swing(void);
// Function that manages the gait cycle through an FSM
int GaitFSM(GaitFSMState init_state);

#endif