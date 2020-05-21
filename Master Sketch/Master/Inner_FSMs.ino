/**
 * Function to monitor speed of Stand to Sit motion
 */
void Sit() {  // TODO: change how speed is changed to be more dynamic
    double scalar = accX;
    double scalarGs = scalar / 9.81;
    if (scalar > SIT_X_TH_POS) { // shin pointing down
        acc_const-= scalarGs;
        acc_const = acc_const > 1 ? acc_const : 1;
        ramp_down_const -= 0.1 * scalarGs;
        ramp_down_const = ramp_down_const > 0.1 ? ramp_down_const : 0.1;
        ramp_down_const = ramp_down_const < 0.9 ? ramp_down_const : 0.9;
        calcParabConsts();
        rotate(SIT_ANG);
    } else if (scalar < SIT_X_TH_NEG) { // Shin pointing up
        acc_const += scalarGs;
        acc_const = acc_const > 1 ? acc_const : 1;
        ramp_down_const += 0.1 * scalarGs;
        ramp_down_const = ramp_down_const > 0.1 ? ramp_down_const : 0.1;
        ramp_down_const = ramp_down_const < 0.9 ? ramp_down_const : 0.9;
        calcParabConsts();
        rotate(SIT_ANG);
    }
}

/**
 * Function to monitor speed of Sit to Stand motion
 */
void Stand() {
    double scalar = accX;
    double scalarGs = scalar / 9.81;
    if (scalar > STAND_X_TH_POS) { // Shin Pointing down
        acc_const += scalarGs;
        acc_const = acc_const > 1 ? acc_const : 1;
        ramp_down_const += 0.1 * scalarGs;
        ramp_down_const = ramp_down_const > 0.1 ? ramp_down_const : 0.1;
        ramp_down_const = ramp_down_const < 0.9 ? ramp_down_const : 0.9;
        calcParabConsts();
        rotate(MAX_EXT_ANG);
    } else if (scalar < STAND_X_TH_NEG) { // Shin Pointing up
        acc_const -= scalarGs;
        acc_const = acc_const > 1 ? acc_const : 1;
        ramp_down_const -= 0.1 * scalarGs;
        ramp_down_const = ramp_down_const > 0.1 ? ramp_down_const : 0.1;
        ramp_down_const = ramp_down_const < 0.9 ? ramp_down_const : 0.9;
        calcParabConsts();
        rotate(MAX_EXT_ANG);
    }
}

/**
 * Function to straighten the leg
 */
void Straighten_Leg() {
    double scalar = accX;
    double scalarGs = scalar / 9.81;
    if (scalar > STRAIGHT_X_TH_POS) {  // Shin Pointing down
        acc_const += scalarGs;
        acc_const = acc_const > 1 ? acc_const : 1;
        ramp_down_const += 0.1 * scalarGs;
        ramp_down_const = ramp_down_const > 0.1 ? ramp_down_const : 0.1;
        ramp_down_const = ramp_down_const < 0.9 ? ramp_down_const : 0.9;
        calcParabConsts();
        rotate(MAX_EXT_ANG);
    } else if (scalar < STRAIGHT_X_TH_NEG) {  // Shin Pointing up
        acc_const -= scalarGs;
        acc_const = acc_const > 1 ? acc_const : 1;
        ramp_down_const -= 0.1 * scalarGs;
        ramp_down_const = ramp_down_const > 0.1 ? ramp_down_const : 0.1;
        ramp_down_const = ramp_down_const < 0.9 ? ramp_down_const : 0.9;
        calcParabConsts();
        rotate(MAX_EXT_ANG);
    }
}

/**
 * Function to retract the leg during stairs or hurdles
 */
void Retract() {
    rotate(RET_STATE_ANG);
}

/**********************************************************
 * Functions for GAIT FSM
 *********************************************************/


void Bend_Knee() {
    rotate(GAIT_BEND_KNEE_ANGLE);
}

void Retract_Knee() {
    rotate(GAIT_RETRACT_KNEE_ANGLE);
}

void Extend_Knee() {
    rotate(MAX_EXT_ANG);
}

// --------------------------------------------------------------------------------------------------------------

int GaitFSM() {
    switch(gait_curr_state) {
        case HEEL_OFF:
            Bend_Knee();
            if (lcFront <= GAIT_HEEL_OFF_SWING_RET_TH ) {
                gait_curr_state = SWING_RET;
            }
            return 0;
        case SWING_RET:
            Retract_Knee();
             if (accX > GAIT_SWING_RET_SWING_EXT_TH) { // TODO: Alex Kyu commented this back in, is this suppose to be here?
                 gait_curr_state = SWING_EXT; // TODO
             } // TODO
            return 0;
        case SWING_EXT:
            Extend_Knee();
            if (lcBack > GAIT_SWING_EXT_END_TH) {
                gait_curr_state = HEEL_OFF; // set it back to the first state for the next run of the Gait FSM
            }
            return 1;
        default:
            return 0;
    }
}
