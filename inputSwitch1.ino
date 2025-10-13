int pd = 3;
int pu = 4;
int ipu = 2;
int r = 12;
int y = 11;
int g = 10;

void setup(){
  pinMode(pd, INPUT_PULLUP);
  pinMode(pu, INPUT_PULLUP);
  pinMode(ipu, INPUT_PULLUP);
  pinMode(r, OUTPUT);
  pinMode(y, OUTPUT);
  pinMode(g, OUTPUT);
}

void loop() {
  if(digitalRead(pd) == HIGH){
    digitalWrite(r, HIGH);
  }

  if(digitalRead(pu) == LOW)
  {
    digitalWrite(y, HIGH);
  }
  if(digitalRead(ipu) == LOW){
    
    digitalWrite(g, HIGH);
  }
}