#include <SPI.h>

const int ss1Pin = 10;
const int ss2Pin = 9;
const int mosiPin = 11;
const int misoPin = 12
const int sck = 13;


void setup() {
  Serial.begin(9600);
  analogReadResolution(12);
  digitalWrite(ssPin, HIGH);
  SPI.begin();
  // put your setup code here, to run once:
  SPI.beginTransaction(SPISettings(2000000,MSBFIRST,SPI_MODE0));
}

void loop() {


}

byte SPIRW(int pin, int address, int cmd) {
  digitalWrite(pin, LOW);
  SPI.transfer(address);
  ret = SPI.transfer(cmd);
  digitalWrite(pin, HIGH);
  return ret;
}
