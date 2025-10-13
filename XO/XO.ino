// Tic-Tac-Toe (XO) on Arduino using FSM
// Play via Serial Monitor (baud 9600, No line ending recommended)

enum State { START, X_TURN, O_TURN, CHECK_WIN, X_WIN, O_WIN, DRAW, END_STATE };
State gameState = START;

char board[9];     // board slots ' ', 'X', 'O'
char lastPlayer;   // last player who moved

// ---------- Function prototypes ----------
void clearBoard();
void printBoard();
bool checkWin(char player);
bool boardFull();
int getMoveFromSerial(); // returns 0-8 for valid move, -1 otherwise
String readLine();       // read a line from Serial

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("=== Arduino Tic-Tac-Toe (XO) ===");
  Serial.println("Play: type 1-9 to place (positions shown on board).");
  Serial.println("When game ends, type 'r' to restart.");
}

void loop() {
  switch (gameState) {
    case START:
      clearBoard();
      Serial.println();
      Serial.println("New game started. Player X goes first.");
      printBoard();
      gameState = X_TURN;
      break;

    case X_TURN: {
      Serial.println("Player X: enter position (1-9):");
      int pos = getMoveFromSerial();
      if (pos != -1) {
        if (board[pos] == ' ') {
          board[pos] = 'X';
          lastPlayer = 'X';
          printBoard();
          gameState = CHECK_WIN;
        } else {
          Serial.println("That position is already taken. Try again.");
        }
      }
    } break;

    case O_TURN: {
      Serial.println("Player O: enter position (1-9):");
      int pos = getMoveFromSerial();
      if (pos != -1) {
        if (board[pos] == ' ') {
          board[pos] = 'O';
          lastPlayer = 'O';
          printBoard();
          gameState = CHECK_WIN;
        } else {
          Serial.println("That position is already taken. Try again.");
        }
      }
    } break;

    case CHECK_WIN:
      if (checkWin('X')) gameState = X_WIN;
      else if (checkWin('O')) gameState = O_WIN;
      else if (boardFull()) gameState = DRAW;
      else {
        // switch turns
        if (lastPlayer == 'X') gameState = O_TURN;
        else gameState = X_TURN;
      }
      break;

    case X_WIN:
      Serial.println(">>> Player X WINS! <<<");
      gameState = END_STATE;
      break;

    case O_WIN:
      Serial.println(">>> Player O WINS! <<<");
      gameState = END_STATE;
      break;

    case DRAW:
      Serial.println(">>> Draw! <<<");
      gameState = END_STATE;
      break;

    case END_STATE:
      Serial.println("Game over. Type 'r' and press Enter to restart.");
      // wait for 'r' or 'R'
      if (Serial.available()) {
        String s = readLine();
        s.trim();
        if (s.length() > 0 && (s.charAt(0) == 'r' || s.charAt(0) == 'R')) {
          gameState = START;
        }
      }
      break;
  } // switch
}

// ---------- Helper functions ----------

void clearBoard() {
  for (int i = 0; i < 9; i++) board[i] = ' ';
}

void printBoard() {
  Serial.println();
  // If slot empty show number (1-9), otherwise show X/O
  for (int i = 0; i < 9; i++) {
    char disp = (board[i] == ' ') ? (char)('1' + i) : board[i];
    Serial.print(" ");
    Serial.print(disp);
    Serial.print(" ");
    if ((i + 1) % 3 == 0) Serial.println();
    else Serial.print("|");
  }
  Serial.println();
}

// check 8 win patterns
bool checkWin(char player) {
  const int patterns[8][3] = {
    {0,1,2}, {3,4,5}, {6,7,8}, // rows
    {0,3,6}, {1,4,7}, {2,5,8}, // cols
    {0,4,8}, {2,4,6}           // diags
  };
  for (int i = 0; i < 8; i++) {
    if (board[patterns[i][0]] == player &&
        board[patterns[i][1]] == player &&
        board[patterns[i][2]] == player) {
      return true;
    }
  }
  return false;
}

bool boardFull() {
  for (int i = 0; i < 9; i++) if (board[i] == ' ') return false;
  return true;
}

// Read user input and parse a move 1-9
// Returns 0..8 for valid move, -1 if no valid input yet
int getMoveFromSerial() {
  if (Serial.available()) {
    String line = readLine();
    line.trim();
    if (line.length() == 0) return -1;
    // allow user to type multiple chars; take first meaningful
    char c = line.charAt(0);
    if (c >= '1' && c <= '9') {
      return (c - '1');
    } else {
      Serial.println("Invalid input. Enter a number 1-9.");
      return -1;
    }
  }
  return -1;
}

// Read until newline or timeout; returns string (may be empty)
String readLine() {
  // Use readStringUntil to collect until '\n'
  String s = Serial.readStringUntil('\n');
  return s;
}
// // -------- FSM States --------
// enum State { START, X_TURN, O_TURN, CHECK_WIN, X_WIN, O_WIN, DRAW, END };
// State gameState = START;

// // -------- XO Board --------
// char board[9];   // เก็บสถานะกระดาน XO
// char lastPlayer; // ผู้เล่นล่าสุด

// // -------- Function Prototypes --------
// void clearBoard();
// void printBoard();
// bool checkWin(char player);
// bool boardFull();
// int getMove();

// void setup() {
//   Serial.begin(9600);
//   Serial.println("Welcome to Arduino Tic-Tac-Toe!");
// }

// void loop() {
//   switch (gameState) {

//     case START:
//       clearBoard();
//       Serial.println("New Game! Player X starts.");
//       printBoard();
//       gameState = X_TURN;
//       break;

//     case X_TURN: {
//       Serial.println("Player X, choose position (1-9): ");
//       int pos = getMove();
//       if (pos != -1 && board[pos] == ' ') {
//         board[pos] = 'X';
//         lastPlayer = 'X';
//         printBoard();
//         gameState = CHECK_WIN;
//       }
//     } break;

//     case O_TURN: {
//       Serial.println("Player O, choose position (1-9): ");
//       int pos = getMove();
//       if (pos != -1 && board[pos] == ' ') {
//         board[pos] = 'O';
//         lastPlayer = 'O';
//         printBoard();
//         gameState = CHECK_WIN;
//       }
//     } break;

//     case CHECK_WIN:
//       if (checkWin('X')) gameState = X_WIN;
//       else if (checkWin('O')) gameState = O_WIN;
//       else if (boardFull()) gameState = DRAW;
//       else {
//         if (lastPlayer == 'X') gameState = O_TURN;
//         else gameState = X_TURN;
//       }
//       break;

//     case X_WIN:
//       Serial.println(">>> Player X WINS! <<<");
//       gameState = END;
//       break;

//     case O_WIN:
//       Serial.println(">>> Player O WINS! <<<");
//       gameState = END;
//       break;

//     case DRAW:
//       Serial.println(">>> DRAW! <<<");
//       gameState = END;
//       break;

//     case END:
//       Serial.println("Game Over. Type 'r' to restart.");
//       if (Serial.available()) {
//         char c = Serial.read();
//         if (c == 'r' || c == 'R') {
//           gameState = START;
//         }
//       }
//       break;
//   }
// }

// // -------- Helper Functions --------
// void clearBoard() {
//   for (int i = 0; i < 9; i++) board[i] = ' ';
// }

// void printBoard() {
//   Serial.println();
//   for (int i = 0; i < 9; i++) {
//     Serial.print(board[i] == ' ' ? (char)('1' + i) : board[i]);
//     if ((i + 1) % 3 == 0) Serial.println();
//     else Serial.print(" | ");
//   }
//   Serial.println();
// }

// bool checkWin(char player) {
//   int winPatterns[8][3] = {
//     {0,1,2}, {3,4,5}, {6,7,8}, // row
//     {0,3,6}, {1,4,7}, {2,5,8}, // col
//     {0,4,8}, {2,4,6}           // diag
//   };
//   for (int i = 0; i < 8; i++) {
//     if (board[winPatterns[i][0]] == player &&
//         board[winPatterns[i][1]] == player &&
//         board[winPatterns[i][2]] == player) {
//       return true;
//     }
//   }
//   return false;
// }

// bool boardFull() {
//   for (int i = 0; i < 9; i++) {
//     if (board[i] == ' ') return false;
//   }
//   return true;
// }

// int getMove() {
//   if (Serial.available()) {
//     char c = Serial.read();
//     if (c >= '1' && c <= '9') {
//       return c - '1'; // แปลง '1'-'9' เป็น index 0-8
//     }
//   }
//   return -1; // ยังไม่ได้ input ที่ถูกต้อง
// }