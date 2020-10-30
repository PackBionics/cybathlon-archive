#include "Math.h"

/**
 * Initializes motor
 */
void Init_Motors()
{
    pinMode(PWM, OUTPUT);
    pinMode(DIR, OUTPUT);
    pinMode(MTR_ENABLE, OUTPUT);
    analogWrite(PWM,0);
    digitalWrite(DIR,HIGH);
    analogWrite(MTR_ENABLE,128);
}

/**
 * calculates the parabola constants, a, b, and c for determining speed based on distance from desired angle
 * 
 * @param index - index used to help distinguish which constants to use/manipulate depending on whether the knee is rotating or if the CAM is fixing location
 */
void calcParabConsts(int index) {
    // determine start speed
    int s = MIN_SSPEED > curr_speed[index] ? MIN_SSPEED : curr_speed[index];
    // determine constants a, b, and c for quadratic
    int delta_ang = abs(dest_ang[index] - init_ang[index]);
    a[index] = -4.0 * (float) acc_const[index] / (float) delta_ang + 2.0 * (float) s / ((float) delta_ang * (float) delta_ang);
    b[index] = 4.0 * (float) acc_const[index] - 3.0 * (float) s / (float) delta_ang;
    c[index] = (float) s;
}


void stall_check(int new_ang, int curr_ang, int index) {
  long time_diff = 0;
  if (prev_ang[index] == -100) {
    prev_ang[index] = curr_ang;
  } else if (prev_ang[index] == curr_ang) {
    time_diff = micros() - init_time[index];
  } else {
    init_time[index] = micros();
    prev_ang[index] = curr_ang;
  }
  if (time_diff > STALL_TIME) {
    curr_speed[index] = curr_speed_stall[index] + (255 - curr_speed_stall[index]) / 3;
    curr_speed_stall[index] = curr_speed[index];
    stall_on = true;
    if (((encKnee > MAX_RET_ANG || encCAM > MAX_CAM_ANG) && curr_dir[index] == MTR_BACKWARD) || ((encKnee < MAX_EXT_ANG  || encCAM < MIN_CAM_ANG) && curr_dir[index] == MTR_FORWARD)) {
      curr_speed[index] = 0;
      curr_speed_stall[index] = 0;
      stall_on = false;
    } else if (curr_ang == new_ang) {
      curr_speed[index] = 0;
      curr_speed_stall[index] = 0;
      stall_on = false;
    }
    curr_speed[index] = curr_speed[index] > 255 ? 255 : curr_speed[index];
  }
  if (stall_on) {
    curr_speed[index] = curr_speed[index] > curr_speed_stall[index] ? curr_speed[index] : curr_speed_stall[index];
  }
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
    if (index == 1) {
      angle = angle > MAX_CAM_ANG ? MAX_CAM_ANG : angle;
      angle = angle < MIN_CAM_ANG ? MIN_CAM_ANG : angle;
    } else {
      angle = angle > MAX_RET_ANG ? MAX_RET_ANG : angle;
      angle = angle < MAX_EXT_ANG ? MAX_EXT_ANG : angle;
    }
    // Check to see if new movement was instantiated
    if (angle != dest_ang[index]) {
        init_movement[index] = false;
    }
    int encAngle = index == 1 ? encCAM : encKnee;

    // determine if direction needs changing and if it needs to ramp down
    int tmp_direction = angle > encAngle ? MTR_BACKWARD : MTR_FORWARD;
    bool reverse = false;
    if (curr_speed[index] != 0 && tmp_direction != curr_dir[index]) {
        reverse = true;
        //Ramp Down to 0 speed
        if (curr_speed[index] >= 20 && updated_sensors_motor) {
            curr_speed[index] -= curr_speed[index]*ramp_down_const[index];
        } else if (updated_sensors_motor) {
            curr_speed[index] = 0;
            ramp_down_const[0] = RMP_DWN_CONST; // reset ramp_down_const after finishing the ramp down
            ramp_down_const[1] = RMP_DWN_CONST_FIX;
        } // else curr_speed doesn't change until boolean is reset on timer (based on interrupt)
    }

    // If it is a new movement and doesn't need to ramp down, instantiate motor movement
    if (!init_movement[index] && !reverse) {
        init_movement[index] = true;
        dest_ang[index] = angle;
        init_ang[index] = encAngle;     // this is ONLY set here because this is where we want to "start" the movement from a 0 power or positive (same direction) power state
        curr_dir[index] = tmp_direction;
        stall_on = false;
        // determine constants a, b, and c for quadratic
        calcParabConsts(index);
    }
    if (!reverse) {
      int delta_ang = abs(encAngle - init_ang[index]);
      curr_speed[index] = a[index] * delta_ang * delta_ang + b[index] * delta_ang + c[index];
//      Serial.println(curr_speed[index]);
      curr_dir[index] = tmp_direction;
      if (abs(encAngle - angle) > RANGE_STOP) {
        curr_speed[index] = curr_speed[index] > MIN_SSPEED ? curr_speed[index] : MIN_SSPEED; // if the speed is too low, have minimum speed kick in to keep motor moving
        stall_check(angle, encAngle, index);
      } else if (encKnee > MAX_RET_ANG || encKnee < MAX_EXT_ANG || encCAM > MAX_CAM_ANG || encCAM < MIN_CAM_ANG) { // another check to make sure that motor doesn't go out of bounds for both encoder ranges
        curr_speed[index] = 0;
        curr_speed_stall[index] = 0;
        stall_on = false;
      } else {
        curr_speed[index] = 0;
        curr_speed_stall[index] = 0;
        stall_on = false;
        acc_const[0] = ACC_CONST; // reset acc_const once reaching final destination
        acc_const[1] = ACC_CONST_FIX;
      }
    }
    if (((encKnee > MAX_RET_ANG || encCAM > MAX_CAM_ANG) && curr_dir[index] == MTR_BACKWARD) || ((encKnee < MAX_EXT_ANG  || encCAM < MIN_CAM_ANG) && curr_dir[index] == MTR_FORWARD)) {
      curr_speed[index] = 0;
    }
    curr_speed[index] = curr_speed[index] > 255 ? 255 : curr_speed[index];

    // write the new speed and direction to the pins
    digitalWrite(DIR, curr_dir[index]);
    analogWrite(PWM, curr_speed[index]);

    // set this to false - this is how we use the interrupt as a timer to update speed periodically without separate timer
    updated_sensors_motor = false;
}

/**
 * converts the encoder CAM reading to give what the corresponding knee encoder should read
 */
int enc_convert() {
  if (encKnee < 0)
    return enc_conversion[0];
  if (encKnee > 115)
    return enc_conversion[115];
  return enc_conversion[encKnee];  //TODO: change to encKnee to 
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
  if (abs(required_angle - encCAM) > RANGE_STOP_CAM) {  //TODO: use encCAM to compare against?
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
 * Writes to Serial output the new calibration numbers by doing the following steps:
 * 1.  rotate the knee to full extension (0 degrees - code implements -2 because of RANGE_STOP)
 * 2.  resetting the CAM encoder to 0
 * 3.  rotating the knee slowly to a fully retracted position (MAX_RET_ANG)
 * 4.  displaying the corresponding expected CAM angle for each knee angle
 * 5.  waits for user input to continue with the program
 */
void auto_cal_enc() {
  if (i2c_flag) {
    Update_I2C();
  }
  while (encKnee != 0) {
    if (i2c_flag) {
      Update_I2C();
    }
    Serial.println(encKnee);
    rotate_helper(0, 0);
  }
  setZeroSPI(ENC_1);
  delay(1000);
  int init_knee = -1000;
  do {
//    Serial.println("h4");
    if (i2c_flag) {
//      Serial.println("h5");
      Update_I2C();
//      tic = micros()-toc;
//      toc = micros();
    }
    analogWrite(PWM, 100);
    digitalWrite(DIR, MTR_BACKWARD);
    if (encKnee != init_knee) {
//      Serial.println("h6");
      Serial.print(encKnee);
      Serial.print("\t");
      Serial.print(encCAM);
      Serial.println(",");
      init_knee = encKnee;
    }
  } while (encKnee < MAX_RET_ANG);
  analogWrite(PWM, 0);
  digitalWrite(DIR, MTR_FORWARD);
  // Wait until user input to continue to main program
  // We prompt for G - but never check for it
  Serial.println("Press G and Enter to finish Calibration");
  while(Serial.available() < 1);
  // now we clear the serial buffer.
  while(Serial.available() > 0) {
    byte dummyread = Serial.read();
  }
}

/**
 * TODO: This function will ensure the cam is at the correct angle with the knee in order to keep the cables in tension as the leg extends
 */
void cableTension() {
    
}
