#define PWM         9                   //Pin for Power of motor.
#define DIR         10                  //Pin for Direction of the motor.

int vel = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PWM, OUTPUT);
  pinMode(DIR, OUTPUT);  
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    
    if (input == 'w') {
      if (vel == 0) {
        digitalWrite(DIR, HIGH);
      }
      vel += 25;
    }
    
    if (input == 's') {
      if (vel == 0) {
        digitalWrite(DIR, LOW);
      }
      vel -= 25;
    }
    
  }
  analogWrite(PWM, abs(vel));
  Serial.println(vel);
}
