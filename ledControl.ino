int r1 = 9;
int r2 = 8;
int r3 = 7;

void setup()
{
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
}

void loop()
{
  digitalWrite(r1, 0);
  digitalWrite(r2, 1);
  pinMode(r3, INPUT);
  delay(500);
  pinMode(r3, OUTPUT);
  pinMode(r1, INPUT);
  digitalWrite(r2, 1);
  digitalWrite(r3, 0);
  delay(500);
  pinMode(r1, INPUT);
  digitalWrite(r2, 0);
  digitalWrite(r3, 1);
  delay(500);
  pinMode(r1, OUTPUT);
  pinMode(r3, INPUT);
  digitalWrite(r1, 1);
  digitalWrite(r2, 0);
  delay(500);
  pinMode(r3, OUTPUT);
  pinMode(r2, INPUT);
  digitalWrite(r1, 0);
  digitalWrite(r3, 1);
  delay(500);
  pinMode(r2, OUTPUT);
  pinMode(r2, INPUT);
  digitalWrite(r1, 1);
  digitalWrite(r3, 0);
  delay(500);
  pinMode(r2, OUTPUT);
}