#define onboard 13

void setup() 
{
  pinMode(onboard, OUTPUT);
}

void loop()
{
  digitalWrite(onboard, 0);
  delay(300);
  digitalWrite(onboard, 1);
  delay(1000);
}
