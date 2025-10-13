void draw_grid() {
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = ST77XX_CYAN;
  tft.drawLine(14, 30, 14, 130, color);
  tft.drawLine(47, 30, 47, 130, color);
  tft.drawLine(80, 30, 80, 130, color);
  tft.drawLine(114, 30, 114, 130, color);
  tft.drawLine(14, 30, 114, 30, color);
  tft.drawLine(14, 63, 114, 63, color);
  tft.drawLine(14, 96, 114, 96, color);
  tft.drawLine(14, 130, 114, 130, color);
}

void ShowWinner(int winner) {
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(22, 50);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.println("Winner!");
  tft.setCursor(56, 80);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  if (winner == 1) tft.println("O");
  if (winner == 2) tft.println("X");
}

void Draw() {
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(40, 50);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(2);
  tft.println("Draw");
}

int CheckWinFunc(int target) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      bool check;
      if (pins[possible_line_component[i][j]] == target) {
        if (j == 2) return i;
      } else break;
    }
  }
  return -1;
}

int consoleSerial() {
  while (1) {
    if (mySerial.available()) {
      int number = mySerial.parseInt();
      return number;
    }
  }
}

void drawCross(int i) {
  tft.drawLine(pins_Xposition[i] - 10, pins_Yposition[i] - 10, pins_Xposition[i] + 10, pins_Yposition[i] + 10, ST77XX_GREEN);
  tft.drawLine(pins_Xposition[i] - 10, pins_Yposition[i] + 10, pins_Xposition[i] + 10, pins_Yposition[i] - 10, ST77XX_GREEN);
}

void eraseCross(int i) {
  tft.drawLine(pins_Xposition[i] - 10, pins_Yposition[i] - 10, pins_Xposition[i] + 10, pins_Yposition[i] + 10, ST77XX_BLACK);
  tft.drawLine(pins_Xposition[i] - 10, pins_Yposition[i] + 10, pins_Xposition[i] + 10, pins_Yposition[i] - 10, ST77XX_BLACK);
}

int SpaceIndexlist[9] = { -1 };
int selIdx = -1;       
int tempPinPlayer = -1; 

void memoryReset() {
  selIdx = -1;
  tempPinPlayer = -1;
  SpaceIndexCount = -1;
}

void HARDmemoryReset() {
  for (int i = 0; i < 9; i++) {
    pins[i] = 0;
  }
}

void makeSpaceIndexList() {
  memset(SpaceIndexlist, -1, sizeof(SpaceIndexlist));
  int count = 0;
  for (int i = 0; i < 9; i++) {
    if (pins[i] == 0) {
      SpaceIndexlist[count++] = i;
    }
  }
  SpaceIndexCount = count;
}


void playerTempPin() {
  memoryReset();
  if (tempPinPlayer == -1) {
    makeSpaceIndexList();
    selIdx = 0;
    tempPinPlayer = SpaceIndexlist[selIdx];
    drawCross(tempPinPlayer);
  }
  while (1) {
    int action = consoleSerial();

    if (action == 2 && SpaceIndexCount > 0) {
      eraseCross(tempPinPlayer);
      selIdx = (selIdx + 1) % SpaceIndexCount;
      tempPinPlayer = SpaceIndexlist[selIdx];
      drawCross(tempPinPlayer);
      delay(350); 
    }

    if (action == 1 && SpaceIndexCount > 0) {
      if (selIdx > 0) {
        eraseCross(tempPinPlayer);
        selIdx = selIdx - 1;  
        tempPinPlayer = SpaceIndexlist[selIdx];
        drawCross(tempPinPlayer);
        delay(350);
      }
    }

    if (action == 5) {
      eraseCross(tempPinPlayer);
      pins[tempPinPlayer] = 2;
      draw_pin();
      return;
    }
  }
}


void draw_pin() {
  for (int i = 0; i < 9; i++) {
    if (pins[i] == 1) tft.drawCircle(pins_Xposition[i] + 1, pins_Yposition[i], 13, ST77XX_RED);
    if (pins[i] == 2) {
      tft.drawLine(pins_Xposition[i] - 10, pins_Yposition[i] - 10, pins_Xposition[i] + 10, pins_Yposition[i] + 10, ST77XX_YELLOW);
      tft.drawLine(pins_Xposition[i] - 10, pins_Yposition[i] + 10, pins_Xposition[i] + 10, pins_Yposition[i] - 10, ST77XX_YELLOW);
    }
  }
}
