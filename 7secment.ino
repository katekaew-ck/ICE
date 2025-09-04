int num[] = {B0011000,B11000000,B01101011,B11101001,B11001100,B10101101,B10101111,B11100000,B11101111,B11101101,B11111000,B11011001};
const int pin[] = {5,6,7,8,9,10,11,12};
int now=1;
long ans=0;
void setup(){ 
  DDRD = 0b11110000;
  DDRB = 0b00111111;
  ans = random(1,10);
  Serial.begin(115200);
  Serial.println(ans);
}

void loop(){
    PORTD=~num[now];
    PORTB=~num[now];

    if (!digitalRead(3))
    {
      now++;
      if(now==10)
        now=1;
      delay(500);
    }
      if (!digitalRead(2))
    {
      if(now > ans)
      {
        PORTD=num[10];
        PORTB=num[10];
      }
      else if(now < ans)
      {
        PORTD=num[11];
        PORTB=num[11];
      }
      else 
      {
        PORTD=num[0];
        PORTB=num[0];
        ans=random(1,10);
        Serial.println(ans);
      }
      delay(500);
    }
}