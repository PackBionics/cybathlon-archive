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
 * 
 * @param index - index used to help distinguish which constants to use/manipulate depending on whether the knee is rotating or if the CAM is fixing location
 */
void calcParabConsts(int index) {
    // determine start speed
    int s = MIN_SSPEED > curr_speed ? MIN_SSPEED : curr_speed;
    // determine constants a, b, and c for quadratic
    int delta_ang = abs(dest_ang - init_ang);
    a[index] = -4.0 * (float) acc_const[index] / (float) delta_ang + 2.0 * (float) s / ((float) delta_ang * (float) delta_ang);
    b[index] = 4.0 * (float) acc_const[index] - 3.0 * (float) s / (float) delta_ang;
    c[index] = (float) s;
}

/**
 * Rotates the leg to the specified angle
 * If a new angle is given, then the function will first determine whether it needs to reverse
 *    If it does not need to reverse, then it will adjust the speed arc and continue in its trajectory
 *    If the given angle is the in the opposite direction of the way the motor is currently spinning,
 *      then the motor will ramp down first before instantiating the movement from a 0 speed state
 * 
 * @param angle - the destination angle
 * @param index - index used to help distinguish which constants to use/manipulate depending on whether the knee is rotating or if the CAM is fixing location
 */
void rotate_helper(int angle, int index) {
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
            curr_speed -= curr_speed*ramp_down_const[index];
        } else if (updated_sensors_motor) {
            curr_speed = 0;
            ramp_down_const[0] = RMP_DWN_CONST; // reset ramp_down_const after finishing the ramp down
            ramp_down_const[1] = RMP_DWN_CONST_FIX;
        } // else curr_speed doesn't change until boolean is reset on timer (based on interrupt)
    }

    // If it is a new movement and doesn't need to ramp down, instantiate motor movement
    if (!init_movement && !reverse) {
        init_movement = true;
        dest_ang = angle;
        init_ang = encKnee;     // this is ONLY set here because this is where we want to "start" the movement from a 0 power or positive (same direction) power state
        curr_dir = tmp_direction;

        // determine constants a, b, and c for quadratic
        calcParabConsts(index);
    }
    if (!reverse) {
        int delta_ang = abs(encKnee - init_ang);
        curr_speed = a[index] * delta_ang * delta_ang + b[index] * delta_ang + c[index];
        if (abs(encKnee - angle) > RANGE_STOP) {
            curr_speed = curr_speed > MIN_SSPEED ? curr_speed : MIN_SSPEED; // if the speed is too low, have minimum speed kick in to keep motor moving
        } else {
            curr_speed = 0;
            acc_const[0] = ACC_CONST; // reset acc_const once reaching final destination
            acc_const[1] = ACC_CONST_FIX;
        }
    }
    curr_speed = curr_speed > 255 ? 255 : curr_speed;

    // write the new speed and direction to the pins
    digitalWrite(DIR, curr_dir);
    analogWrite(PWM, curr_speed);

    // set this to false - this is how we use the interrupt as a timer to update speed periodically without separate timer
    updated_sensors_motor = false;
}

/**
 * converts the encoder CAM reading to give what the corresponding knee encoder should read
 */
int enc_convert() {
  return enc_conversion[encCAM + 18];
}

/**
 * Wrapper function for rotate to dictate the behavior of the motor:
 *    if the encoder of the knee and cam are correct (matching each other via the hardcoded values [see enc_convert()]), then it will rotate to the given angle
 *    if the encoder of the knee and cam are not correct (not macthing each other via the hardcoded values), then it will rotate to fix the difference
 *    
 * @param angle is the desired angle to rotate to
 */
void rotate(int angle) {
  int required_angle = enc_convert();
  if (abs(required_angle - encKnee) > RANGE_STOP) {
    rotate_helper(required_angle, 1); // rotate for fixing the CAM position
  } else {
    rotate_helper(angle, 0);  // regular rotate
  }
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
