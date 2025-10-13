void setup () {
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(2,INPUT_PULLUP);
  
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
}
int state[3] = {0};
	
int funtion(int N){
  delay(100);
  if (N == 0)
  {N = 1;}
  else 
  { N = 0;}
  return N;
}
void loop(){
  int buttonState_r = digitalRead(3);
  int buttonState_y = digitalRead(4);
  int buttonState_g = digitalRead(2);
  
  if (buttonState_r == HIGH) {
    state[0] = funtion(state[0]);
}
  if (buttonState_y == LOW) {
    state[1] = funtion(state[1]);
  }
  if (buttonState_g == LOW) {
    state[2] = funtion(state[2]);
  }
  digitalWrite(12,state[0]);
  digitalWrite(11,state[1]);
  digitalWrite(10,state[2]);
}

  // digitalWrite(pin, !digitalRead(pin));