#define PWM         9                   //Pin for Power of motor.
#define DIR         10                  //Pin for Direction of the motor.

int speed = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PWM, OUTPUT);
  pinMode(DIR, OUTPUT);  
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();

    // speeding up
    if (input == 'w')
      if (speed == 0)
        digitalWrite(DIR, HIGH);

    // slowing down
    if (input == 's')
      if (speed == 0)
        digitalWrite(DIR, LOW);
    
    speed += 10;
  }
  analogWrite(PWM, speed);
}
