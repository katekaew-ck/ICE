const int red_n = 3;
const int yellow_n = 4;
const int green_n = 5;
const int button_n = 6;

const int red_e = 10;
const int yellow_e = 11;
const int green_e = 12;
const int button_e = 13;

const int red_w = 8;
const int green_w = 7;
const int button_w = 9;

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

int output_pins[8] = { green_e, yellow_e, red_e, green_n, yellow_n, red_n, green_w, red_w };
int input, input1, input2, input3;

struct State {
  unsigned long ST_Out;
  unsigned long Time;
  unsigned long NextSt[8];
};

typedef const struct State SType;

SType FSM[11] = {
  { B10001100, 6000, { goN, waitN, goN, waitN, waitN, waitN, waitN, waitN } },
  { B10010100, 2000, { goE, goE, goE, goE, goW, goW, goW, goW } },
  { B10100001, 6000, { goE, goE, waitE, waitE, waitE, waitE, waitE, waitE } },
  { B10100010, 2000, { goN, goN, goN, goN, goW, goW, goW, goW } },
  { B01100100, 4000, { waitOffW1, waitOffW1, waitOffW1, waitOffW1, waitOffW1, waitOffW1, waitOffW1, waitOffW1 } },
  { B00100100, 1000, { waitOnW1, waitOnW1, waitOnW1, waitOnW1, waitOnW1, waitOnW1, waitOnW1, waitOnW1 } },
  { B01100100, 1000, { waitOffW2, waitOffW2, waitOffW2, waitOffW2, waitOffW2, waitOffW2, waitOffW2, waitOffW2 } },
  { B00100100, 1000, { waitOnW2, waitOnW2, waitOnW2, waitOnW2, waitOnW2, waitOnW2, waitOnW2, waitOnW2 } },
  { B01100100, 1000, { waitOffW3, waitOffW3, waitOffW3, waitOffW3, waitOffW3, waitOffW3, waitOffW3, waitOffW3 } },
  { B00100100, 1000, { waitOnW3, waitOnW3, waitOnW3, waitOnW3, waitOnW3, waitOnW3, waitOnW3, waitOnW3 } },
  { B01100100, 1000, { goN, goE, goN, goE, goN, goE, goN, goE } }
};
unsigned long ST = 0;

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(output_pins[i], OUTPUT);
  }
  pinMode(button_n, INPUT_PULLUP);
  pinMode(button_e, INPUT_PULLUP);
  pinMode(button_w, INPUT_PULLUP);
}

void loop() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(output_pins[i], !((FSM[ST].ST_Out >> i) & 1));
  }
  delay(FSM[ST].Time);

  input1 = !digitalRead(button_n);
  input2 = !digitalRead(button_e);
  input3 = !digitalRead(button_w);

  input = (input3 * 4) + (input1 * 2) + input2;
  ST = FSM[ST].NextSt[input];
}