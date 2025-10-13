


// int ENA = 5;
// int ENB = 6;
// int INA = 11;
// int INB = 10;
// int INC = 9;
// int IND = 8;
// int delayTurn = 475i;
// int delayGo = 1000;
// int speedGo = 200;
// void setup() {
//   // set all the motor control pins to outputs
//   pinMode(ENA, OUTPUT);
//   pinMode(ENB, OUTPUT);
//   pinMode(INA, OUTPUT);
//   pinMode(INB, OUTPUT);
//   pinMode(INC, OUTPUT);
//   pinMode(IND, OUTPUT);

// // set speed to 200 out of possible range 0~255
//   analogWrite(ENA, 215);
//   analogWrite(ENB, 200); 

//   //  go
//   digitalWrite(INA, HIGH);
//   digitalWrite(INB, LOW);
//   digitalWrite(INC, HIGH);
//   digitalWrite(IND, LOW);
//   delay(delayGo);
//  // turn
//   digitalWrite(INA, LOW);
//   digitalWrite(INB, HIGH);
//   digitalWrite(INC, LOW);
//   digitalWrite(IND, LOW);
//   delay(delayTurn);
//   // go
//   digitalWrite(INA, HIGH);
//   digitalWrite(INB, LOW);
//   digitalWrite(INC, HIGH);
//   digitalWrite(IND, LOW);
//   delay(delayGo);
//   // turn
//   digitalWrite(INA, LOW);
//   digitalWrite(INB, HIGH);
//   digitalWrite(INC, LOW);
//   digitalWrite(IND, LOW);
//   delay(delayTurn);
//   // go
//   digitalWrite(INA, HIGH);
//   digitalWrite(INB, LOW);
//   digitalWrite(INC, HIGH);
//   digitalWrite(IND, LOW);
//   delay(delayGo);
//   // turn
//   digitalWrite(INA, LOW);
//   digitalWrite(INB, HIGH);
//   digitalWrite(INC, LOW);
//   digitalWrite(IND, LOW);
//   delay(delayTurn);
//   // go
//   digitalWrite(INA, HIGH);
//   digitalWrite(INB, LOW);
//   digitalWrite(INC, HIGH);
//   digitalWrite(IND, LOW);
//   delay(delayGo);
//   // stop
//   digitalWrite(INA, LOW);
//   digitalWrite(INC, LOW);
// }
// void loop() {}