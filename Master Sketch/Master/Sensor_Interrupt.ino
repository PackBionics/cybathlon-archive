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

  Timer1.initialize(10000);
  Timer1.attachInterrupt(Read_Sensors, 10000);
}

/**
 * Function to update sensor global variables
 */
void Read_Sensors() {
  button_state = digitalRead(LOCKED_BUTTON);
  updated_sensors_motor = true;
  i2c_flag = true;
}

void Update_I2C() {
  lcFront = Read_LC1();
  lcBack = Read_LC2();
  lcLeft = Read_LC3();
  lcRight = Read_LC4();
  sensors_event_t event; 
  mma.getEvent(&event);
  accX = -1.0 * event.acceleration.x;
  accY = -1.0 * event.acceleration.y;
  accZ = -1.0 * event.acceleration.z;
//  accX = getX();
//  accY = getY();
//  accZ = getZ();
  encKnee = bitToDegrees(getPositionSPI(ENC_0, RES14));
  encCAM = bitToDegrees(getPositionSPI(ENC_1, RES14));
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
  i2c_flag = false;
}


/**
 * Interrupt function
 */
//ISR(__vectorTIMER_COMPA_vect) {
//  Serial.println("Interrupt");
//  Read_Sensors();
//}
