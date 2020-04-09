/**
 * Function to monitor speed of Stand to Sit motion
 */
void Sit() {
    if (getX() > SIT_X_TH_POS) {
//    curr_speed++; // make a change to the acc const?  cascade change down a, b, and c constants (how fast to ramp up?)
        acc_const++;
        ramp_down_const += 0.1;
        calcParabConsts();
        rotate(RET_ANG);
    } else if (getX() < SIT_X_TH_NEG) {
//    curr_speed--;
        acc_const--;
        ramp_down_const -= 0.1;
        calcParabConsts();
        rotate(RET_ANG);
    }
}

/**
 * Function to monitor speed of Sit to Stand motion
 */
void Stand() {
    if (getX() > STAND_X_TH_POS) {
//    curr_speed++;
        acc_const++;
        ramp_down_const += 0.1;
        calcParabConsts();
        rotate(EXT_ANG);
    } else if (getX() < STAND_X_TH_NEG) {
//    curr_speed--;
        acc_const--;
        ramp_down_const -= 0.1;
        calcParabConsts();
        rotate(EXT_ANG);
    }
}

/**
 * Function to straighten the leg
 */
void Straighten_Leg() {
    if (getX() > STRAIGHT_X_TH_POS) {
        acc_const++;
        ramp_down_const += 0.1;
        calcParabConsts();
        rotate(EXT_ANG);
    } else if (getX() < STRAIGHT_X_TH_NEG) {
        acc_const--;
        ramp_down_const -= 0.1;
        calcParabConsts();
        rotate(EXT_ANG);
    }
}

/**
 * Function to straighten the leg
 */
void Retract() {
    if (getX() > RETRACT_X_TH_POS) {
        acc_const++;
        ramp_down_const += 0.1;
        calcParabConsts();
        rotate(RET_ANG);
    } else if (getX() < RETRACT_X_TH_NEG) {
        acc_const--;
        ramp_down_const -= 0.1;
        calcParabConsts();
        rotate(RET_ANG);
    }
}

void Free_Swing() {
    // Need to figure out how to get g_ang instead of using EXT_ANG and RET_ANG to be able to better control speed through rotate function
    // either use getX and getY or somehow figure out how to use transient rotation from accelerometer
    int g_ang = encKnee + acc_to_ang(getX());
    if (abs(getX() + getY()) > G_TH) {
        if (getY() > G_TH_MAX || getY() < G_TH_MIN) {
            if (getX() < FS_X_TH_NEG) {
                rotate(g_ang);
            } else {
                rotate(g_ang);
            }
        } else {
            analogWrite(PWM, 0);
            curr_speed = 0;
        }
    } else {
        analogWrite(PWM, 0);
        curr_speed = 0;
    }
}

void Bend_Knee() {
    rotate(GAIT_BEND_KNEE_ANGLE);
}

void Retract_Knee() {
    rotate(GAIT_RETRACT_KNEE_ANGLE);
}

void Extend_Knee() {
    rotate(EXT_ANG);
}

// --------------------------------------------------------------------------------------------------------------

int GaitFSM() {
    switch(gait_curr_state) {
        case HEEL_OFF:
            Bend_Knee();
            if (lcFront <= GAIT_HEEL_OFF_SWING_RET_TH ) {
                gait_curr_state = SWING_RET;
            }
            return 1;
        case SWING_RET:
            Retract_Knee();
            // if (yAcc == ankles_aligned_threshold) {
            gait_curr_state = SWING_EXT;
            return 1;
        case SWING_EXT:
            Extend_Knee();
            if (lcBack > GAIT_SWING_EXT_END_TH) {
                gait_curr_state = HEEL_OFF; // set it back to the first state for the next run of the Gait FSM
            }
            return 0;
        default:
            return 1;
    }
}
