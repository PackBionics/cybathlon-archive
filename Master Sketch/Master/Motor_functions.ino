void Init_Motors()
{
  pinMode(PWM, OUTPUT);
  pinMode(DIR, OUTPUT);  
  analogWrite(PWM,0);
  digitalWrite(DIR,HIGH);
}
