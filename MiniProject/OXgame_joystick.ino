#define VRy 2
#define SW 3

#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 6);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(12, 1);
  digitalWrite(13, 0);
}

int console(int VRyc, int SWc) {
  int VRy_value = analogRead(VRyc);
  int SW_value = analogRead(SWc);
  if (VRy_value > 1000) return 1;
  if (VRy_value < 100) return 2;
  if (SW_value < 20) return 5;
  return 0;
}

int consoleCheck() {
  int VRx_value = analogRead(1);
  int VRy_value = analogRead(2);
  int SW_value = analogRead(3);
  Serial.print("VRx_value => ");
  Serial.println(VRx_value);
  Serial.print("VRy_value => ");
  Serial.println(VRy_value);
  Serial.print("SW_value => ");
  Serial.println(SW_value);
  Serial.println("---------------------------");
}

void loop() {
  mySerial.println(console(VRy, SW));
  delay(200);
}