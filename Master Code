#include <AFMotor.h>
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(A0, A1);
SoftwareSerial ArmSerial(13, A2);

AF_DCMotor motorFL(1);
AF_DCMotor motorFR(2);
AF_DCMotor motorBL(3);
AF_DCMotor motorBR(4);

char cmd;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  ArmSerial.begin(9600);

  motorFL.setSpeed(200);
  motorFR.setSpeed(200);
  motorBL.setSpeed(200);
  motorBR.setSpeed(200);

  motorFL.run(RELEASE);
  motorFR.run(RELEASE);
  motorBL.run(RELEASE);
  motorBR.run(RELEASE);
}

void loop() {
  if (BTSerial.available()) {
    cmd = BTSerial.read();

    if (cmd == 'F') {
      motorFL.run(FORWARD); motorFR.run(FORWARD);
      motorBL.run(FORWARD); motorBR.run(FORWARD);
    }
    else if (cmd == 'B') {
      motorFL.run(BACKWARD); motorFR.run(BACKWARD);
      motorBL.run(BACKWARD); motorBR.run(BACKWARD);
    }
    else if (cmd == 'L') {
      motorFL.run(BACKWARD); motorFR.run(FORWARD);
      motorBL.run(BACKWARD); motorBR.run(FORWARD);
    }
    else if (cmd == 'R') {
      motorFL.run(FORWARD); motorFR.run(BACKWARD);
      motorBL.run(FORWARD); motorBR.run(BACKWARD);
    }
    else if (cmd == 'S') {
      motorFL.run(RELEASE); motorFR.run(RELEASE);
      motorBL.run(RELEASE); motorBR.run(RELEASE);
    }
    else if (strchr("qawsedoc", cmd) != NULL) {
      ArmSerial.write(cmd);
    }
  }
}
