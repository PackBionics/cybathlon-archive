void Init_Interrupt() {
  //set timer1 interrupt at 20Hz
  TCCR1A = 0;// set entire TCCR0A register to 0
  TCCR1B = 0x0C;// set WGM12 to CTC mode and set prescale to 256
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for about 20hz increments
  OCR1A = 3124;// = (16*10^6) / (20*4096) - 1 (must be <256) 
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
}

void Read_Sensors() {
  encKnee = getPositionSPI(ENC_0, RES14);
  encCAM = getPositionSPI(ENC_1, RES14);
  lcFront = Read_LC1();
  lcBack = Read_LC2();
  lcLeft = Read_LC3();
  lcRight = Read_LC4();
}

ISR(TIMER_COMPA_vect) {
    Read_Sensors();
}
