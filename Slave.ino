#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial CommandSerial(2, 3);

Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo gripperServo;

int basePos = 90;
int shoulderPos = 90;
int elbowPos = 90;
int gripperPos = 90;
const int step = 3;

void setup() {
  Serial.begin(9600);
  CommandSerial.begin(9600);

  baseServo.attach(3);
  shoulderServo.attach(5);
  elbowServo.attach(6);
  gripperServo.attach(9);

  baseServo.write(basePos);
  shoulderServo.write(shoulderPos);
  elbowServo.write(elbowPos);
  gripperServo.write(gripperPos);
}

void loop() {
  if (CommandSerial.available()) {
    char cmd = CommandSerial.read();

    if (cmd == 'q') basePos += step;
    if (cmd == 'a') basePos -= step;
    if (cmd == 'w') shoulderPos += step;
    if (cmd == 's') shoulderPos -= step;
    if (cmd == 'e') elbowPos += step;
    if (cmd == 'd') elbowPos -= step;
    if (cmd == 'o') gripperPos = 160;
    if (cmd == 'c') gripperPos = 20;

    basePos = constrain(basePos, 0, 180);
    shoulderPos = constrain(shoulderPos, 10, 170);
    elbowPos = constrain(elbowPos, 10, 170);
    gripperPos = constrain(gripperPos, 10, 170);

    baseServo.write(basePos);
    shoulderServo.write(shoulderPos);
    elbowServo.write(elbowPos);
    gripperServo.write(gripperPos);
    delay(15);
  }
}
