#define ECHO 13
#define TRIG 12
#define signal_4 A0
#define signal_3 A1
#define signal_2 A2
#define signal_1 A3
#define signal_0 A4
#define signal_5 A5
#define enA 10
#define in1 9
#define in2 8
#define enB 6
#define in3 5
#define in4 4

#define mission_x 5
#define mission_y 5
#define home_x 1
#define home_y 1
#define checkPoint_x 6
#define checkPoint_y 6

#define calibrate_L 0
#define calibrate_R 10

int threshold[] = {500, 500, 500, 500, 500, 500};

int value_0 = 0;
int value_1 = 0;
int value_2 = 0;
int value_3 = 0;
int value_4 = 0;
int value_5 = 0;

int map_area_survey[8][8] = {
    {100, 100, 100, 100, 100, 100, 100, 100},
    {100, 0, 0, 0, 0, 0, 0, 100},
    {100, 0, 0, 0, 0, 0, 0, 100},
    {100, 0, 100, 0, 0, 0, 0, 100},
    {100, 0, 0, 0, 0, 100, 0, 100},
    {100, 0, 0, 0, 0, 0, 0, 100},
    {100, 0, 0, 0, 0, 0, 0, 100},
    {100, 100, 100, 100, 100, 100, 100, 100}};


int map_area[8] [8] = {
    {100, 100, 100, 100, 100, 100, 100, 100},
    {100, 0, 0, 0, 0, 0, 0, 100},
    {100, 0, 0, 0, 0, 0, 0, 100},
    {100, 0, 100, 0, 0, 0, 0, 100},
    {100, 0, 0, 0, 0, 100, 0, 100},
    {100, 0, 0, 0, 0, 0, 0, 100},
    {100, 1, 0, 0, 0, 0, 0, 100},
    {100, 100, 100, 100, 100, 100, 100, 100}};

int dir = 1; // 0-up 1-right 2-down 3-left
int priority_dir_CheckPoint[4] = {2, 3, 1, 0};
int priority_dir_Home[4] = {2, 3, 1, 0};

int count = 50;
int my_x = 1;
int my_y = 1;
int position_x_change[] = {0, 1, 0, -1};
int position_y_change[] = {1, 0, -1, 0};


int check_box()
{
  return 1;
}
void getpriority(int priority_dir[])
{
  int index = 0;
  int check[4] = {0, 0, 0, 0};
  for (size_t i = 0; i < 4; i++)
  {
    if (map_area[my_x + position_x_change[priority_dir_CheckPoint[i]]][my_y + position_y_change[priority_dir_CheckPoint[i]]] == 0)
    {
      priority_dir[index++] = priority_dir_CheckPoint[i];
      check[priority_dir_CheckPoint[i]] = 1;
    }
  }
    int max_value=-1;
    for (size_t i = 0; i < 4; i++)
    {
      if(check[i]==0&&
        map_area[my_x+position_x_change[i]][my_y+position_y_change[i]]<map_area[my_x][my_y]
        &&map_area[my_x+position_x_change[i]][my_y+position_y_change[i]]>max_value)
      {
        max_value=map_area[my_x+position_x_change[i]][my_y+position_y_change[i]];
        priority_dir[index]=i;
        break;
      }
    }
    check[priority_dir[index]]=1;
  
}
void survey()
{
  while (1)//5box
  {
    int priority_dir[4] = {-1, -1, -1, -1};
    getpriority(priority_dir);
    for (int i = 0; i < 4; i++)
    {
      while (dir != priority_dir[i])
      {
        SR();
        dir = (dir + 1) % 4;
        // SL();
        // dir = (dir + 3) % 4;
      }

      if (map_area_survey[my_x + position_x_change[dir]][my_y + position_y_change[dir]] < 99 && check_box())
      {
        forward();
        my_x += position_x_change[dir];
        my_y += position_y_change[dir];
        count++;
        map_area_survey[my_x][my_y] = count;
        break;
      }
    }
  }
}

void move(int L, int R)
{
  if (R > 0)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    R *= -1;
  }

  if (L > 0)
  {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else
  {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    L *= -1;
  }

  if (L - calibrate_L < 0)
  {
    analogWrite(enB, 0);
  }
  else
  {
    analogWrite(enB, L - calibrate_L);
  }

  if (R - calibrate_R < 0)
  {
    analogWrite(enA, 0);
  }
  else
  {
    analogWrite(enA, R - calibrate_R);
  }
}
void move_line()
{
  if (value_1 > threshold[1] && value_3 > threshold[3])
    move(120, 120);
  else if (value_1 < threshold[1] && value_3 > threshold[3])
    move(80, 120);
  else if (value_1 > threshold[1] && value_3 < threshold[3])
    move(120, 80);
  else if (value_0 < threshold[0] && value_4 < threshold[4])
    move(0, 0);
}

void forward()
{
  Readsensor();
  while (value_0 > threshold[0] || value_3 > threshold[3])
  {
    Readsensor();
    move_line();
  }
  move(120, 120);
  delay(380);
  move(0, 0);
}
void SR()
{
  Readsensor();
  while (value_4 > threshold[4])
  {
    Readsensor();
    move(100, -100);
  }
  while (value_3 > threshold[3])
  {
    Readsensor();
    move(100, -100);
  }
  while (value_2 > threshold[2])
  {
    Readsensor();
    move(80, -80);
  }
  move(0, 0);
}
void SL()
{
  Readsensor();
  while (value_0 > threshold[0])
  {
    Readsensor();
    move(-100, 100);
  }
  while (value_1 > threshold[1])
  {
    Readsensor();
    move(-100, 100);
  }
  while (value_2 > threshold[2])
  {
    Readsensor();
    move(-80, 80);
  }
  move(0, 0);
}
void Readsensor()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);

  // convert to distance in cm
  int distance = duration * 0.034 / 2;

  value_0 = analogRead(signal_0); // 0 - 1023
  value_1 = analogRead(signal_1);
  value_2 = analogRead(signal_2);
  value_3 = analogRead(signal_3);
  value_4 = analogRead(signal_4);
  value_5 = analogRead(signal_5);
}

void setup()
{
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // forward();
  // forward();
  // forward();
  // SR();
  // forward();
  // forward();
  // forward();
  // SR();
  // SR();
  // delay(3000);
  // forward();
  // forward();
  // forward();
  // SL();
  // forward();
  // forward();
  // forward();
  SR();
  forward();
  SL();
  forward();
  SR();
  forward();
  SL();
  forward();
  SR();
  forward();
  SL();
  forward();
  SL();
  forward();
  SL();
  forward();
  SR();
  forward();
  SL();
  forward();
  SR();
  forward();
  SL();
  forward();
}

void loop()
{
}
