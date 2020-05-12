#include <TimerOne.h>

/**
 * Initializes Interrupt
 */
void Init_Interrupt() {
//  //set timer1 interrupt at 20Hz
//  TCCR1A = 0;// set entire TCCR0A register to 0
//  TCCR1B = 0x0C;// set WGM12 to CTC mode and set prescale to 256
//  TCNT1  = 0;//initialize counter value to 0
//  // set compare match register for about 20hz increments
//  OCR1A = 3124;// = (16*10^6) / (20*4096) - 1 (must be <256) 
//  // enable timer compare interrupt
//  TIMSK1 |= (1 << OCIE1A);

  Timer1.initialize(50000);
  Timer1.attachInterrupt(Read_Sensors, 50000);
}

/**
 * Function to update sensor global variables
 */
void Read_Sensors() {
//  if (read_vel) {
//    vel = 10 * encKnee
//  }
  updated_sensors_motor = true;
  encKnee = bitToDegrees(getPositionSPI(ENC_0, RES14));
  encCAM = bitToDegrees(getPositionSPI(ENC_1, RES14));
  lcFront = Read_LC1();
  lcBack = Read_LC2();
  lcLeft = Read_LC3();
  lcRight = Read_LC4();
//  accX = getX();
//  accY = getY();
//  accZ = getZ();
  if (encKnee == MAX_RET_ANG) {
    fully_retracted = true;
    fully_extended = false;
    retracted = true;
  } else if (encKnee == MAX_EXT_ANG) {
    fully_extended = true;
    fully_retracted = false;
  } else {
    fully_extended = false;
    fully_retracted = false;
  }

}

/**
 * Interrupt function
 */
//ISR(__vectorTIMER_COMPA_vect) {
//  Serial.println("Interrupt");
//  Read_Sensors();
//}
