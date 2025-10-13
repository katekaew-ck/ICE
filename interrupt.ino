int button1 = 3;
int button2 = 4;
int button3 = 2;
int r = 12;
int y = 11;
int g = 10;
long last = 0;
volatile bool sw1Pressed = false;
volatile bool sw3Pressed = false;

void setup(){
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(r, OUTPUT);
  pinMode(y, OUTPUT);
  pinMode(g, OUTPUT);
  attachInterrupt(1,onlyred,FALLING);
  attachInterrupt(0,close,FALLING);

}

void loop() {
  if(digitalRead(button1) == HIGH, digitalRead(button2) == HIGH, digitalRead(button3) == HIGH){
    digitalWrite(r, 0);
    digitalWrite(y, 0);
    digitalWrite(g, 1);
    delay(7000);
    digitalWrite(r, 0);
    digitalWrite(y, 0);
    digitalWrite(g, 1);
    delay(3000);
    digitalWrite(r, 0);
    digitalWrite(y, 1);
    digitalWrite(g, 0);
    delay(3000);
    digitalWrite(r, 0);
    digitalWrite(y, 1);
    digitalWrite(g, 0);
    delay(1000);
    digitalWrite(r, 1);
    digitalWrite(y, 0);
    digitalWrite(g, 0);
    delay(5000);
    digitalWrite(r, 1);
    digitalWrite(y, 0);
    digitalWrite(g, 0);
    delay(000);
  }
}
void onlyred() {
    last = millis();
  digitalWrite(r, 1);
  digitalWrite(y, 0);
  digitalWrite(g, 0);
  while(millis()-last >= 5000){
    digitalWrite(r, 0);
  }
}

void close() {
  last = millis();
  digitalWrite(r,0);
  digitalWrite(y,0);
  digitalWrite(g,0);
  delay(5000);
}