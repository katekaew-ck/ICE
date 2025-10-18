const int red_n = 10;
const int yellow_n = 9;
const int green_n = 8;
const int button_n = 3;

const int red_e = 6;
const int yellow_e = 5;
const int green_e = 4;
const int button_e = 2;

const int red_w = 13;
const int green_w = 12;
const int button_w = 11;

#define goN 0
#define waitN 1
#define goE 2
#define waitE 3
#define goW 4
#define waitOffW1 5
#define waitOnW1 6
#define waitOffW2 7
#define waitOnW2 8
#define waitOffW3 9
#define waitOnW3 10

struct State {
unsigned long ST_Out;
unsigned long Time;
unsigned long NextSt[8];};

typedef const struct State SType;
  
SType FSM[11] = {
  {B10001100, 6000, {goN, waitN, goN,waitN,waitN, waitN,waitN, waitN}},
  {B10010100, 2000, {goE, goE, goE, goE, goW, goW ,goW, goW}},
  {B10100001, 6000, {goE, goE, waitE, waitE, waitE, waitE, waitE, waitE}},
  {B10100010, 2000, {goN, goN, goN, goN,goW ,goW, goW, goW}},
  {B01100100, 4000, {waitOffW1, waitOffW1, waitOffW1, waitOffW1, waitOffW1, waitOffW1, waitOffW1, waitOffW1}},//goW
  {B00100100, 1000, {waitOnW1, waitOnW1, waitOnW1, waitOnW1, waitOnW1, waitOnW1, waitOnW1, waitOnW1}},
  {B01100100, 1000, {waitOffW2, waitOffW2, waitOffW2, waitOffW2, waitOffW2, waitOffW2, waitOffW2, waitOffW2}},
  {B00100100, 1000, {waitOnW2, waitOnW2, waitOnW2, waitOnW2, waitOnW2, waitOnW2, waitOnW2, waitOnW2}},
  {B01100100, 1000, {waitOffW3, waitOffW3, waitOffW3, waitOffW3, waitOffW3, waitOffW3, waitOffW3, waitOffW3}},
  {B00100100, 1000, {waitOnW3, waitOnW3, waitOnW3, waitOnW3, waitOnW3, waitOnW3, waitOnW3, waitOnW3}},
  {B01100100, 1000, {goN, goE, goN, goE, goN, goE, goN, goE}}
};
unsigned long ST=0; 

void setup() {
pinMode(red_n, OUTPUT);
pinMode(yellow_n, OUTPUT);
pinMode(green_n, OUTPUT);
pinMode(button_n, INPUT);
pinMode(red_e, OUTPUT);
pinMode(yellow_e, OUTPUT);
pinMode(green_e, OUTPUT);
pinMode(button_e, INPUT);
pinMode(red_w, OUTPUT);
pinMode(green_w, OUTPUT);
pinMode(button_w, INPUT);
}

int input,input1, input2, input3;

void loop() {
digitalWrite(red_n, FSM[ST].ST_Out & B00100000);
digitalWrite(yellow_n, FSM[ST].ST_Out & B00010000);
digitalWrite(green_n, FSM[ST].ST_Out & B00001000);
digitalWrite(red_e, FSM[ST].ST_Out & B00000100);
digitalWrite(yellow_e, FSM[ST].ST_Out & B00000010);
digitalWrite(green_e, FSM[ST].ST_Out & B00000001);
digitalWrite(red_w, FSM[ST].ST_Out & B10000000);
digitalWrite(green_w, FSM[ST].ST_Out & B01000000);
delay(FSM[ST].Time);

input1 = digitalRead(button_n);
input2 = digitalRead(button_e);
input3 = digitalRead(button_w);
  
input = (input3*4)+(input1*2)+input2;
ST = FSM[ST].NextSt[input];
} 
