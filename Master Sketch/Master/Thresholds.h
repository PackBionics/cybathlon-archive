// Thresholds for main FSM
#define MIDSTANCE_SIT_TH 400 // threshold for determining to go from MIDSTANCE to SIT State (uses heel loading)
#define MIDSTANCE_GAIT_TH 400 // threshold for determining MIDSTANCE to GAIT State (uses toe loading)
#define SIT_STAND_TH 400 // threshold for determining SIT to STAND State (uses heel loading)
#define GAIT_H_STRIKE_TH 400 // threshold for determining GAIT to H_STRIKE State (uses heel loading)
#define RETRACTION_FULL_EXT_LCFRONT_TH 400 // threshold for determining RETRACTION to FULL_EXT State front loadcell load
#define RETRACTION_FULL_EXT_LCBACK_TH 400 // threshold for determining RETRACTION to FULL_EXT State back loadcell load
#define RETRACTION_FULL_EXT_LCLEFT_TH 400 // threshold for determining RETRACTION to FULL_EXT State left loadcell load
#define RETRACTION_FULL_EXT_LCRIGHT_TH 400 // threshold for determining RETRACTION to FULL_EXT State right loadcell load
#define RETRACTION_H_STRIKE_LCBACK_TH 400 // threshold for determining RETRACTTION to H_STRIKE State for back loadcell load
#define RETRACTION_H_STRIKE_LCBACKFRONT_TH 400 // threshold for determining RETRACTION to H_STRIKE State for back loadcell and front loadcell difference

#define ZERO_ERROR_LC 50 // error for how close to 0 LCs are to be deemed "0" force
#define ZERO_ERROR_ENC 1 // error for how close to 0 encoders are to be deemed "0"

// Thresholds for Sit and Stand function
#define SIT_X_TH_POS  400 // threshold for x accelerometer to determine if the pilot's leg is pointing upwards (shin pointing upwards) for sitting
#define SIT_X_TH_NEG  400 // threshold for x accelerameter to determine if the pilot's leg is pointing downwards (shin pointing downwards) for sitting
#define STAND_X_TH_POS  400 // threshold for x accelerometer to determine if the pilot's leg is pointing upwards (shin pointing upwards) for standing
#define STAND_X_TH_NEG  400 // threshold for x accelerameter to determine if the pilot's leg is pointing downwards (shin pointing downwards) for standing

// Thresholds for freeswing gravity
#define G_TH  400 // threshold for reasonable range of gravity (magnitude of x and y direction [perpendicular to shank and down the leg])
#define G_TH_MIN  400 // minimum threshold for gravity in the y direction (should be relatively close to 9.81)
#define G_TH_MAX  400 // maximum threshold for gravity in the y direction (should be relatively close to 9.81)
#define FS_X_TH_NEG  400 // x threshold hold for determining whether the shin is pointing forward (and therefore should swing forward)
