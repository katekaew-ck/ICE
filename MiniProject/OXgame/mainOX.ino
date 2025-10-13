int pins[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int pins_Xposition[9] = { 31, 64, 97, 31, 64, 97, 31, 64, 97 };

int pins_Yposition[9] = { 47, 47, 47, 80, 80, 80, 113, 113, 113 };

int possible_line_component[8][3] = { { 0, 3, 6 }, { 1, 4, 7 }, { 2, 5, 8 }, { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, { 0, 4, 8 }, { 2, 4, 6 } };


struct dataset {
  int check;
  int position;
  int possible_line;
  int possible_lineIndex[8];
  int possible_member[8];
};
struct dataset pinO[10];
struct dataset pinX[10];

void possible_lineANDmemberCheck(int pin) {
  for (int target = 1; target <= 2; target++) {
    int target1 = 3 - target;
    for (int i = 0; i < 8; i++) {
      if (((pins[possible_line_component[i][0]] == target) || (pins[possible_line_component[i][1]] == target) || (pins[possible_line_component[i][2]] == target)) && !((pins[possible_line_component[i][0]] == target1) || (pins[possible_line_component[i][1]] == target1) || (pins[possible_line_component[i][2]] == target1))) {
        if (target == 1) {
          pinO[pin].check = 1;
          pinO[pin].possible_lineIndex[i] = 1;
          pinO[pin].possible_line++;
        } else if (target == 2) {
          pinX[pin].check = 1;
          pinX[pin].possible_lineIndex[i] = 1;
          pinX[pin].possible_line++;
        }
      }
    }
  }
  for (int i = 0; i < 8; i++) {
    if (pinO[pin].possible_lineIndex[i] == 1) {
      for (int j = 0; j < 3; j++) {
        if (pins[possible_line_component[i][j]] == 1) {
          pinO[pin].possible_member[i]++;
        }
      }
    }
    if (pinX[pin].possible_lineIndex[i] == 1) {
      for (int j = 0; j < 3; j++) {
        if (pins[possible_line_component[i][j]] == 2) {
          pinX[pin].possible_member[i]++;
        }
      }
    }
  }
}


int space[9] = { 0 };
int how_many_space() {
  memset(space, 0, sizeof(space));
  int spaceIndex = 0;
  for (int i = 0; i < 9; i++) {
    if (pins[i] == 0) {
      space[spaceIndex++] = i;
    }
  }
  return spaceIndex;
}

int tempPin;
void advance_to_next_empty_pin() {
  int numSpace = how_many_space();
  static int last = -1;
  int current = -1;
  if (last >= 0 && last < 9 && pins[last] == 1) {
    current = last;
  }
  int pick = -1;
  for (int k = 0; k < numSpace; k++) {
    if (space[k] > current) {
      pick = space[k];
      break;
    }
  }
  if (pick == -1) pick = space[0];
  if (current >= 0 && current < 9 && pins[current] == 1) {
    pins[current] = 0;
  }
  pins[pick] = 1;
  last = pick;
  tempPin = pick;
}


void bot() {
  memset(pinO, 0, sizeof(pinO));
  memset(pinX, 0, sizeof(pinX));
  for (int pin = 0; pin < 10; pin++) {
    pinO[pin].possible_line = 0;
    pinX[pin].possible_line = 0;
    memset(pinO[pin].possible_member, 0, sizeof(pinO[pin].possible_member));
    memset(pinX[pin].possible_member, 0, sizeof(pinX[pin].possible_member));
    memset(pinO[pin].possible_lineIndex, 0, sizeof(pinO[pin].possible_lineIndex));
    memset(pinX[pin].possible_lineIndex, 0, sizeof(pinX[pin].possible_lineIndex));
  }
  possible_lineANDmemberCheck(9);

  how_many_space();
  int space0 = how_many_space();
  if (space0 == 9) {
    int preferred[] = { 0, 2, 4, 6, 8 };
    int r = random(0, 5);
    pins[preferred[r]] = 1;
    draw_pin();
    return;
  }

  for (int event = 0; event < space0; event++) {
    advance_to_next_empty_pin();
    possible_lineANDmemberCheck(tempPin);
    pinO[tempPin].position = tempPin;
    pinO[tempPin].check = 1;
  }
  pins[tempPin] = 0;

  struct target_dataset {
    int position;
    int line_mine_gain;
    int member_mine_gain;
    int special_member_mine_gain;
    int line_enemy_loss;
    int member_enemy_loss;
    int special_member_enemy_loss;
    int score;
  };
  struct target_dataset targetPin[space0];
  memset(targetPin, 0, sizeof(targetPin));

  int targetPinIndex = 0;
  for (int i = 0; i < 9; i++) {
    if (pinO[i].check) {
      targetPin[targetPinIndex].position = pinO[i].position;
      targetPin[targetPinIndex].line_mine_gain = pinO[i].possible_line - pinO[9].possible_line;
      targetPin[targetPinIndex].line_enemy_loss = pinX[9].possible_line - pinX[i].possible_line;
      targetPin[targetPinIndex].member_mine_gain = 0;
      targetPin[targetPinIndex].special_member_mine_gain = 0;
      targetPin[targetPinIndex].member_enemy_loss = 0;
      targetPin[targetPinIndex].special_member_enemy_loss = 0;
      for (int j = 0; j < 8; j++) {
        targetPin[targetPinIndex].member_mine_gain += pinO[i].possible_member[j];
        targetPin[targetPinIndex].member_mine_gain -= pinO[9].possible_member[j];
        targetPin[targetPinIndex].member_enemy_loss += pinX[9].possible_member[j];
        targetPin[targetPinIndex].member_enemy_loss -= pinX[i].possible_member[j];
      targetPinIndex++;
    }
  }
  int maxscore = -10;
  int maxscorePin = 1;
  for (int i = 0; i < targetPinIndex; i++) {
    targetPin[i].score = targetPin[i].line_mine_gain * 10 + targetPin[i].member_mine_gain * 10 + targetPin[i].line_enemy_loss * 10 + targetPin[i].member_enemy_loss * 10;

    if (targetPin[i].score > maxscore) {
      maxscore = targetPin[i].score;
      maxscorePin = targetPin[i].position;
    }
  }
  pins[maxscorePin] = 1;
  draw_pin();
}
