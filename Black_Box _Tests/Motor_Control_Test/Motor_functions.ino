#include "Math.h"

/**
 * Initializes motor
 */
void Init_Motors()
{
    pinMode(PWM, OUTPUT);
    pinMode(DIR, OUTPUT);
    analogWrite(PWM,0);
    digitalWrite(DIR,HIGH);
}

/**
 * calculates the parabola constants, a, b, and c for determining speed based on distance from desired angle
 */
void calcParabConsts() {
    // determine start speed
    int s = MIN_SSPEED > curr_speed ? MIN_SSPEED : curr_speed;
    // determine constants a, b, and c for quadratic
    int delta_ang = abs(dest_ang - init_ang);
    a = -4.0 * (float) acc_const / (float) delta_ang + 2.0 * (float) s / ((float) delta_ang * (float) delta_ang);
    b = 4.0 * (float) acc_const - 3.0 * (float) s / (float) delta_ang;
    c = (float) s;
}

/**
 * Rotates the leg to the specified angle
 * If a new angle is given, then the function will first determine whether it needs to reverse
 *    If it does not need to reverse, then it will adjust the speed arc and continue in its trajectory
 *    If the given angle is the in the opposite direction of the way the motor is currently spinning,
 *      then the motor will ramp down first before instantiating the movement from a 0 speed state
 * 
 * @param angle - the destination angle
 */
void rotate(int angle) {
    // limit the input angles to be between the min and max ranges of the knee's capabilities
    angle = angle > MAX_RET_ANG ? MAX_RET_ANG : angle;
    angle = angle < MAX_EXT_ANG ? MAX_EXT_ANG : angle;
    // Check to see if new movement was instantiated
    if (angle != dest_ang) {
        init_movement = false;
    }

    // determine if direction needs changing and if it needs to ramp down
    int tmp_direction = angle > encKnee ? MTR_BACKWARD : MTR_FORWARD;
    bool reverse = false;
    if (curr_speed != 0 && tmp_direction != curr_dir) {
        reverse = true;
        //Ramp Down to 0 speed
        if (curr_speed >= 20 && updated_sensors_motor) {
            curr_speed -= curr_speed*ramp_down_const;
        } else if (updated_sensors_motor) {
            curr_speed = 0;
            ramp_down_const = RMP_DWN_CONST; // reset ramp_down_const after finishing the ramp down
        } // else curr_speed doesn't change until boolean is reset on timer (based on interrupt)
    }

    // If it is a new movement and doesn't need to ramp down, instantiate motor movement
    if (!init_movement && !reverse) {
        init_movement = true;
        dest_ang = angle;
        init_ang = encKnee;     // this is ONLY set here because this is where we want to "start" the movement from a 0 power or positive (same direction) power state
        curr_dir = tmp_direction;

        // determine constants a, b, and c for quadratic
        calcParabConsts();
    }
    if (!reverse) {
        int delta_ang = abs(encKnee - init_ang);
        curr_speed = a * delta_ang * delta_ang + b * delta_ang + c;
        if (abs(encKnee - angle) > RANGE_STOP) {
            curr_speed = curr_speed > MIN_SSPEED ? curr_speed : MIN_SSPEED; // if the speed is too low, have minimum speed kick in to keep motor moving
        } else {
            curr_speed = 0;
            acc_const = ACC_CONST; // reset acc_const once reaching final destination
        }
    }
    curr_speed = curr_speed > 255 ? 255 : curr_speed;

    // write the new speed and direction to the pins
    digitalWrite(DIR, curr_dir);
    analogWrite(PWM, curr_speed);

    // set this to false - this is how we use the interrupt as a timer to update speed periodically without separate timer
    updated_sensors_motor = false;
}


void Free_Swing() {
    if ( accY < G_TH_Y_ACC) {
        int thetaG = acos(accY / gravAcc) * 180 / PI;
        int thetaH = (accX > 0 ? encKnee - thetaG : encKnee + thetaG);
        rotate(thetaH);
    }
}

/**
 * TODO: This function will ensure the cam is at the correct angle with the knee in order to keep the cables in tension as the leg extends
 */
 void cableTension() {

 }
