// 1 go to checkpoint
// ให้รถวิ่งแบบ ขวา - ขึ้น สลับกัน โดยจะคอยเช็คว่าทางที่จะไปมีกล่องมั้ย ถ้ามีให้ไปอีกทางนึง(ขวา - ขึ้น)
// 2 back to start
// เก็บเส้นทางที่วิ่งไว้ใน array แล้วดึงโดยเริ่มจากตัวสุดท้ายออกมา
// 3 push box
// จะให้รถวิ่งทางขวาแล้วขี้น (แต่ถ้ามีกล่องทางขวาให้ขึ้นแล้วขวา)
#define sensor1 A1
#define sensor2 A2
#define sensor3 A3
#define sensor4 A4
#define sensor5 A5
#define inA 8
#define inB 7
#define inC 4
#define inD 3
#define enA 6
#define enB 5
#define TRIG 11
#define ECHO 10

#define U 0
#define R 1
#define D 2
#define L 3

#define PUSH_UP 10
#define PUSH_RIGHT 11
#define PUSH_DOWN 12
#define PUSH_LEFT 13

#define skip 0
#define turn_right 1
#define u_turn 2
#define turn_left 3

#define BB 30  // black box
#define OB 60  // orange box
#define CP 50  // check point
#define TP 70  // target point
#define SP 80  // start point


int value1 = 0;
int value2 = 0;
int value3 = 0;
int value4 = 0;
int value5 = 0;

int thres = 300;

int map_arr[6][6] = {
  { 0, 0, 0, 0, 0, CP },
  { 0, 0, 0, 0, TP, 0 },
  { 0, BB, OB, 0, 0, 0 },
  { 0, 0, 0, 0, BB, 0 },
  { 0, 0, 0, 0, 0, 0 },
  { SP, 0, 0, 0, 0, 0 },
};



int my_x = 0;
int my_y = 5;

int dx[] = { 0, 1, 0, -1 };  // U,R,D,L
int dy[] = { -1, 0, 1, 0 };  // U,R,D,L

int target_dir = U;

int path[100];
int path_len = 0;

int cur_dir = U;

int direction[4][4] = {
  { skip, turn_right, u_turn, turn_left },
  { turn_left, skip, turn_right, u_turn },
  { u_turn, turn_left, skip, turn_right },
  { turn_right, u_turn, turn_left, skip }
};

void read_sensor() {
  value1 = analogRead(sensor1);
  value2 = analogRead(sensor2);
  value3 = analogRead(sensor3);
  value4 = analogRead(sensor4);
  value5 = analogRead(sensor5);
  Serial.print("  S1: ");
  Serial.print(value1);
  Serial.print("  S2: ");
  Serial.print(value2);
  Serial.print("  S3: ");
  Serial.print(value3);
  Serial.print("  S4: ");
  Serial.print(value4);
  Serial.print("  S5: ");
  Serial.println(value5);
}

bool check_box() {
  return 0;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);
  int distance = duration * 0.034 / 2;

  if (distance < 10) {
    return true;
  } else {
    return false;
  }
}

int move() {
  read_sensor();
  if (value3 < thres && value2 > thres && value4 > thres) {
    forward();
    return 1;
  }

  // ↩️ เบนซ้าย (เส้นไปทางซ้าย)
  else if (value2 < thres && value3 > thres) {
    left();
    return 1;
  }

  // ↪️ เบนขวา (เส้นไปทางขวา)
  else if (value4 < thres && value3 > thres) {
    right();
    return 1;
  }

  // ⚫ ถึงจุดตัด (ทุกตัวเจอดำ) → หยุด
  else if (value1 < thres && value2 < thres && value3 < thres && value4 < thres && value5 < thres) {
    // delay(50);
    stop();
    return 0;  // บอกว่าเจอทางแยก
  }
}

void forward() {
  // Move both motors forward
  digitalWrite(inA, 0);
  digitalWrite(inB, 1);
  digitalWrite(inC, 0);
  digitalWrite(inD, 1);
  analogWrite(enA, 100);
  analogWrite(enB, 120);
}

void left() {
  // Slight correction to left: left motor slower, right faster
  digitalWrite(inA, 0);
  digitalWrite(inB, 1);
  digitalWrite(inC, 0);
  digitalWrite(inD, 1);
  analogWrite(enA, 80);
  analogWrite(enB, 90);
}

void right() {
  // Slight correction to right: right motor slower, left faster
  digitalWrite(inA, 0);
  digitalWrite(inB, 1);
  digitalWrite(inC, 0);
  digitalWrite(inD, 1);
  analogWrite(enA, 110);
  analogWrite(enB, 80);
}

void backward() {
  digitalWrite(inA, 1);
  digitalWrite(inB, 0);
  digitalWrite(inC, 1);
  digitalWrite(inD, 0);
  analogWrite(enA, 120);
  analogWrite(enB, 120);
  delay(150);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void stop() {
  digitalWrite(inA, 0);
  digitalWrite(inB, 1);
  digitalWrite(inC, 0);
  digitalWrite(inD, 1);
  for (int i=0; i<18; i++) {
    analogWrite(enA, 120-i*5);
    analogWrite(enB, 120-i*5);
    delay(10);
  }
  // digitalWrite(inA, 0);
  // digitalWrite(inB, 1);
  // digitalWrite(inC, 0);
  // digitalWrite(inD, 1);
  // analogWrite(enA, 120);
  // analogWrite(enB, 120);
  // delay(180);
  // digitalWrite(inA, 1);
  // digitalWrite(inB, 0);
  // digitalWrite(inC, 1);
  // digitalWrite(inD, 0);
  // analogWrite(enA, 120);
  // analogWrite(enB, 120);
  // delay(150);
  // digitalWrite(inA, 0);
  // digitalWrite(inB, 0);
  // digitalWrite(inC, 0);
  // digitalWrite(inD, 0);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  // turnL();
  // turnR();
  // Uturn();
}

void bae_sai() { 

}

void turnR() {
  digitalWrite(inA, 1);
  digitalWrite(inB, 0);
  digitalWrite(inC, 0);
  digitalWrite(inD, 1);
  read_sensor();
  int black = 0;
  if (value3 > thres){ 

  }
  while (value3 < thres) {
    read_sensor();
    analogWrite(enA, 100);
    analogWrite(enB, 100);
  }
  while (1) {
    read_sensor();
    analogWrite(enA, 90);
    analogWrite(enB, 90);
    if (value3 < thres && value4 > thres) {
      break;
    }
  }

  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void turnL() {
  digitalWrite(inA, 0);
  digitalWrite(inB, 1);
  digitalWrite(inC, 1);
  digitalWrite(inD, 0);
  read_sensor();
  while (value3 < thres) {
    read_sensor();
    analogWrite(enA, 120);
    analogWrite(enB, 120);
    Serial.println("Start turn left");
  }
  while (1) {
    read_sensor();
    analogWrite(enA, 90);
    analogWrite(enB, 90);
    Serial.println("Turning left");
    if (value2 > thres && value3 < thres) {
    // if (value3 < thres) {
      break;
    }
  }

  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

void turn(int target_dir) {
  int action = direction[cur_dir][target_dir];
  switch (action) {
    case skip:
      break;

    case turn_right:
      turnR();
      break;

    case u_turn:
      turnR();
      turnR();
      break;

    case turn_left:
      turnL();
      break;
  }
  cur_dir = target_dir;
}

void push(int target_dir) {
  turn(target_dir);
  while (!move()) {}
  while (move()) {}

  unsigned long push_start = millis();

  while (true) {
    move();
    // Add a timeout safety (e.g., 5 seconds)
    if (millis() - push_start > 5000) {
      Serial.println("Push timeout — stopping");
      break;
    }
  }

  backward();
  // stop()
}


void walker(int target_dir) {
  turn(target_dir);
  while (!move()) {
    // Serial.println("INTERSECT");
  }
  while (move()) {
    // Serial.println("MOVING ON STRAIGHT LINE");
  }

  my_x += dx[target_dir];
  my_y += dy[target_dir];
}

void go_to_checkpoint() {
  Serial.println("Going to checkpoint...");
  while (map_arr[my_y][my_x] != CP) {
    target_dir = (target_dir == R) ? U : R;
    turn(target_dir);

    if (check_box()) {
      target_dir = (target_dir == R) ? U : R;
    }

    walker(target_dir);
    path[path_len++] = target_dir;
    Serial.print("Step : ");
    Serial.print(path_len);
    Serial.print(", ");
    Serial.println(path[path_len-1]);
  }

  Serial.println("Checkpoint reached!");
}

void go_home() {
  Serial.println("Returning home...");

  while (path_len > 0) {
    int last_dir = path[--path_len];
    int back_dir;

    // reverse
    switch (last_dir) {
      case R: back_dir = L; break;
      case L: back_dir = R; break;
      case U: back_dir = D; break;
      case D: back_dir = U; break;
    }

    walker(back_dir);
  }

  Serial.println("Back at start!");
}

int push_path[] = { L, L, PUSH_DOWN, R, D, D, L, L, U, PUSH_RIGHT, D, R, PUSH_UP, PUSH_UP, L, U, PUSH_RIGHT };
int push_path_len = sizeof(push_path) / sizeof(push_path[0]);

int back_path[] = { D, D, D, L, L };
int back_path_len = sizeof(back_path) / sizeof(back_path[0]);

void push_to_target() {
  walker((path[path_len - 1] == R) ? L : D);
  walker((path[path_len - 2] == R) ? L : D);

  for (int i = 0; i < push_path_len; i++) {
    int dir = push_path[i];

    if (path < 10) {
      walker(dir);
    } else {
      push(dir - 10);
    }
  }
}

void back_from_target() {
  for (int i = 0; i < back_path_len; i++) {
    walker(back_path[i]);
  }

  // if right go left
  // if up go down
  walker((path[1] == R) ? L : D);
  walker((path[0] == R) ? L : D);
}


void setup() {
  Serial.begin(9600);
  pinMode(inA, OUTPUT);
  pinMode(inB, OUTPUT);
  pinMode(inC, OUTPUT);
  pinMode(inD, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  go_to_checkpoint();
  // go_home();
  push_to_target();
  back_from_target();
}

void loop() {
}
