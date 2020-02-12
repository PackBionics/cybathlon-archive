// Thresholds for FSM
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

// Thresholds for Sit function
#define SIT_X_TH_POS  400
#define SIT_X_TH_NEG  400
#define STAND_X_TH_POS  400
#define STAND_X_TH_NEG  400
