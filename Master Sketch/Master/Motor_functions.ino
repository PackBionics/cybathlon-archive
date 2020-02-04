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
 * rotate is the base function for turning the motor
 * @param dir - is the direction of that the motor spins
 * @param angle - is the destination angle at the end of the rotation
 * @return the current angle
 */
int rotate(int dir, int angle) {
  digitalWrite(DIR, dir);
  curr_ang = encKnee;
  int threshold_range = dir == 1 ? angle + RANGE_SLOW : angle - RANGE_SLOW; // This may change depending on direction of spinning
  if (curr_speed < MAX_MPWR && curr_ang > threshold_range) {
    curr_speed++;
  } else if (curr_ang < threshold_range && curr_speed != 0) {
    curr_speed--;
  }
  if (curr_ang < angle + RANGE_STOP && curr_ang > angle - RANGE_STOP) { // range of error allowed
    curr_speed = 0;
    analogWrite(PWM, curr_speed);
  } else {
    analogWrite(PWM, curr_speed);
  }
}

// we are assuming high for dir is clockwise
///**
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
