// Angular displacement of knee during HEEL_OFF state of GAIT FSM
#define GAIT_BEND_KNEE_ANGLE 5
// Angular displacement of knee during swing phase 1 of gait fsm
#define GAIT_RETRACT_KNEE_ANGLE 30
// Angular displacement for knee for retraction during stairs/hurdles
#define RET_STATE_ANG 45
// Angular displacement for knee for retraction during sitting
#define SIT_ANG 90

// States in the Gait FSM
enum GaitFSMState {HEEL_OFF, SWING_RET, SWING_EXT};

// Current state of GAIT FSM
GaitFSMState gait_curr_state = HEEL_OFF;

// Function that monitors speed of standing to sitting motion
void Sit(void);
// Function that monitors speed of sitting to standing motion
void Stand(void);
// Function that monitors speed of straightening of the leg motion
void Straighten_Leg(void);
// Function that monitors speed of retracting of the leg motion
void Retract(void);
// Function that manages the gait cycle through an FSM
int GaitFSM(void);


/****************************************************************
* Private
****************************************************************/
//// Function that bends the knee slightly before toe-off in gait swing
//void Bend_Knee();
//
//// Function that retracts knee for first phase of swing in gait
//void Retract_Knee();
//
//// Function that extends knee for second phase of swing in gait
//void Extend_Knee();
