#include <TimerOne.h>

void setup() {
  // put your setup code here, to run once:
  Timer1.initialize(500000);
  Timer1.attachInterrupt(Hello, 500000);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void Hello() {
  Serial.println("Hello");
}
