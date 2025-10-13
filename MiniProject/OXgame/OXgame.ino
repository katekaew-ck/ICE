#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS 10
#define TFT_RST 8
#define TFT_DC 9

#define VRx 0
#define VRy 1
#define SW 2

#define Start 0
#define Xturn 1
#define Oturn 2
#define CheckWin 3

#define IP 5
#define OP 6

#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 6);

long player;
int State = Start;
int PreState = 0;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

struct str {
  unsigned long Time;
  unsigned long NextSt[3];
};

struct str FSM[4] = {
  { 100, { Xturn, Oturn } },
  { 100, { CheckWin } },
  { 100, { CheckWin } },
  { 2000, { Oturn, Xturn } }
};

int SpaceIndexCount = -1;

void draw_grid();
void draw_pin();
void playerTempPin();
void bot();
int CheckWinFunc(int target);
void ShowWinner(int winner);
void Draw();

void setup() {
  randomSeed(analogRead(A4));
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  digitalWrite(7, 1);
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {
  delay(300);
  switch (State) {
    case Start:
      {
        HARDmemoryReset();
        draw_grid();
        draw_pin();
        player = random(1, 3);
        Serial.println(player);
        delay(FSM[State].Time);
        if (player == 1) {
          State = Oturn;
        } else {
          State = Xturn;
        }
      }
      break;

    case Xturn:
      {
        Serial.println("เข้า X แล้วจ้า");
        playerTempPin();
        delay(FSM[State].Time);
        PreState = Xturn;
        State = CheckWin;
      }
      break;

    case Oturn:
      {
        Serial.println("เข้า O แล้วจ้า");
        bot();
        delay(FSM[State].Time);
        PreState = Oturn;
        State = CheckWin;
      }
      break;

    case CheckWin:
      {
        int X_win = CheckWinFunc(2);
        int O_win = CheckWinFunc(1);
        if (X_win >= 0) ShowWinner(2);
        if (O_win >= 0) ShowWinner(1);
        if (how_many_space() == 0 && !(X_win >= 0 || O_win >= 0)) Draw();
        if (!(X_win >= 0 || O_win >= 0) && how_many_space() != 0) {
          State = 3 - PreState;
          return;
        } else State = Start;
        delay(FSM[CheckWin].Time);
      }
      break;
  }
}
