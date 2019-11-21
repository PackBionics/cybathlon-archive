#include "LoadCell.h"
#include "Encoder.h"

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
  loadcell1.begin(LOADCELL_DOUT_PIN1, LOADCELL_SCK_PIN);
  loadcell1.set_scale(LOADCELL_DIVIDER);
  loadcell1.set_offset(0);
  loadcell1.set_gain();
  loadcell2.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN);
  loadcell2.set_scale(LOADCELL_DIVIDER);
  loadcell2.set_offset(0);
  loadcell2.set_gain();
  loadcell3.begin(LOADCELL_DOUT_PIN3, LOADCELL_SCK_PIN);
  loadcell3.set_scale(LOADCELL_DIVIDER);
  loadcell3.set_offset(0);
  loadcell3.set_gain();
  loadcell4.begin(LOADCELL_DOUT_PIN4, LOADCELL_SCK_PIN);
  loadcell4.set_scale(LOADCELL_DIVIDER);
  loadcell4.set_offset(0);
  loadcell4.set_gain();
}

void loop() {
  // put your main code here, to run repeatedly:

}
