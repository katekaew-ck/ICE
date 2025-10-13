const int SpeakerPin = 3;
const int play = 4;
const int record = 5;
const int Pin[] = {12,11,10,9,8,7,6};
int tones[] = {262,294,330,349,392,440,494};
int sound_rec[100] = {0};
int time_r[100] = {0};
int Ftime = 0;
int press = 0;


void setup ()
{
	for (int i=0 ; i<7 ; i++)
    {
      pinMode(Pin[i],INPUT);
    }
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(3,OUTPUT);
  Serial.begin(9600);
}

void loop () {
    for (int i=0 ; i<7 ; i++){
    if (digitalRead(Pin[i]) == 1) {
  note(i);
	}
    }
  int rec = digitalRead(record);
  if (rec == 1)
  {
    sound_rec[100] = {0};
    time_r[100] = {0};
    press = 0;
    delay(50);
	}
  int playb = digitalRead(play);
  if (playb==1){
    for(int a = 0; a < press; a++){
    tone(SpeakerPin,sound_rec[a]);
    delay(time_r[a]);
    noTone(SpeakerPin); 
    delay(250);
    }
  }
}

void note(int i){
  int Sound = digitalRead(Pin[i]);
  Ftime = millis();
  tone(SpeakerPin,tones[i]);
  sound_rec[press] = tones[i];
  while(digitalRead(Pin[i]) == 1){}
  noTone(SpeakerPin);
  time_r[press] = millis() - Ftime;
  press++;
  delay(10);
}
