
void setup() {
  //Set the modes for the SPI IO
  pinMode(SPI_SCLK, OUTPUT);
  pinMode(SPI_MOSI, OUTPUT);
  pinMode(SPI_MISO, INPUT);
  pinMode(ENC_0, OUTPUT);
  pinMode(ENC_1, OUTPUT);

  //Initialize the UART serial connection for debugging
  Serial.begin(BAUDRATE);

  //Get the CS line high which is the default inactive state
  digitalWrite(ENC_0, HIGH);
  digitalWrite(ENC_1, HIGH);
  SPI.setClockDivider(SPI_CLOCK_DIV32);    // 500 kHz
  SPI.begin();


  Serial.begin(9600);
  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  loadcell.set_scale(LOADCELL_DIVIDER);
  loadcell.set_offset(0);
  loadcell.set_gain();
  loadcell2.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN);
  loadcell2.set_scale(LOADCELL_DIVIDER);
  loadcell2.set_offset(0);
  loadcell2.set_gain();
}

void loop() {
  // put your main code here, to run repeatedly:

}
