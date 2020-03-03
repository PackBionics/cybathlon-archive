#define PWM         9                   //Pin for Power of motor.
#define DIR         10                  //Pin for Direction of the motor.

int angle = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PWM, OUTPUT);
  pinMode(DIR, OUTPUT);  
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    
    if (input == 'w') {
      if (speed == 0) {
        digitalWrite(DIR, HIGH);
      }
      speed += 25;
    }
    
    if (input == 's') {
      if (speed == 0) {
        digitalWrite(DIR, LOW);
      }
      speed -= 25;
    }
    
  }
  analogWrite(PWM, abs(speed));
}
