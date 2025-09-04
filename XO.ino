#define size 3
int pin_col[size] = {12, 11, 10};
int pin_row[size] = {7, 6, 5};
int status = 1;

void setup() {
  for(int i=0; i<size; i++){
    pinMode(pin_col[i], OUTPUT);
    pinMode(pin_row[i], OUTPUT);

    digitalWrite(pin_col[i], LOW);
    digitalWrite(pin_row[i], HIGH);
  }
}

void loop(){
  unsigned long long time_start=millis();
  while(millis()-time_start<=1000){
    if(status==1) X();
    else O();
  }
  status=(status+1)%2;
  delay(1);
}

void X(){
  on(0,0);
  on(0,2);
  on(1,1);
  on(2,0);
  on(2,2);
}
void O(){
  on(0,0);
  on(0,1);
  on(0,2);
  on(1,0);
  on(1,2);
  on(2,0);
  on(2,1);
  on(2,2);
}
void allon(){
  for(int i=0; i<size; i++){
    digitalWrite(pin_col[i], 1);
    digitalWrite(pin_row[i], 0);
  }
}

void on(int col, int row){
  for(int i=0; i<size; i++){
    digitalWrite(pin_col[i], LOW);
    digitalWrite(pin_row[i], HIGH);
  }
  
  digitalWrite(pin_col[col], HIGH);
  digitalWrite(pin_row[row], LOW);
  delay(1);
}