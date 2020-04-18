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
    angle = angle > 115 ? 115 : angle;
    angle = angle < 0 ? 0 : angle;
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
//    analogWrite(PWM, 0);

    // set this to false - this is how we use the interrupt as a timer to update speed periodically without separate timer
    updated_sensors_motor = false;
}

/*************************************************************************************
 * Legacy Code
 ************************************************************************************/

//int rot(int angle) {
//    int vel = MAX_MPWR;
//    int slowVel = MAX_MPWR / 2;
//
//    if (encKnee < (angle - RANGE_STOP)) {
//        digitalWrite(DIR, MTR_BACKWARD);
//        if ((angle - encKnee) < RANGE_SLOW)
//            curr_speed = slowVel;
//        else curr_speed = MAX_MPWR;
//    }
//    else if (encKnee > (angle + RANGE_STOP)) {
//        digitalWrite(DIR, MTR_FORWARD);
//        if ((encKnee - angle) < RANGE_SLOW)
//            curr_speed = slowVel;
//        else curr_speed = MAX_MPWR;
//    }
//    else curr_speed = MIN_MPWR;
//
//    analogWrite(PWM, curr_speed);
//}

// /**
// * rotate is the base function for turning the motor
// * @param dir - is the direction of that the motor spins
// * @param angle - is the destination angle at the end of the rotation
// * @return the current angle
// */
//int rotate(int dir, int angle) {
//  digitalWrite(DIR, dir);
//  curr_ang = encKnee;
//  int threshold_range = dir == MTR_FORWARD ? angle + RANGE_SLOW : angle - RANGE_SLOW; // This may change depending on direction of spinning
//  if (curr_speed < MAX_MPWR && curr_ang > threshold_range) {
//    // speed motor up - need more effective implementation here (same for slowing down)
//    curr_speed++;
//  } else if (curr_ang < threshold_range && curr_speed != 0) {
//    curr_speed--;
//  }
//  if (curr_ang < angle + RANGE_STOP && curr_ang > angle - RANGE_STOP) { // range of error allowed
//    curr_speed = 0;
//    analogWrite(PWM, curr_speed);
//  } else {
//    analogWrite(PWM, curr_speed);
//  }
//}

// we are assuming high for dir is clockwise
// /**
// * @param halt is the stopping position
// * @param is the max speed
// * @param dir is the direction
// * @return the current position
// */
//uint16_t rotate(uint16_t halt, uint8_t pwm, uint8_t dir)
//{
//  int curr_pos = getPositionSPI(ENC_0, RES14);
//  int change_dist = dir ? halt - curr_pos : MAX_DIST - (halt - curr_pos);
//  int init_dist = change_dist;
//
//  while (abs(change_dist) > STOP_DIST)
//  {
//    // calculate speed ratio (ramps up and down; fastest at half the distance travelled)
//    int curr_speed = 1 - abs(change_dist - init_dist / 2);
//    int speedM = curr_speed * MOTOR_PWR + MIN_MPWR;
//    // write to the motor to go the desired speed in the desired direction
//    digitalWrite(DIR, dir);
//    analogWrite(PWM, speedM);
//
//    // get new current position
//    curr_pos = getPositionSPI(ENC_0, RES14);
//    change_dist = dir ? halt - curr_pos : MAX_DIST - (halt - curr_pos);
//  }
//  return curr_pos;
//}

//uint16_t stall(uint8_t pwm, uint8_t dir)
//{
//  return 0;
//}
