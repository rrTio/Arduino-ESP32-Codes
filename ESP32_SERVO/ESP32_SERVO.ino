#include <ESP32Servo.h>
Servo servoA;
Servo servoB;
Servo servoC;
Servo servoD; 
Servo servoE;
Servo servoF;
int pinA = 27;
int pinB = 26;
int pinC = 25;
int pinD = 33;
int pinE = 32;
int pinF = 35;

int openValue = 90;
int closeValue = 0;

int delayTime = 500;
void setup() {
  servoA.attach(27);
  servoB.attach(26);
  servoC.attach(25);
  servoD.attach(pinD);
  servoE.attach(pinE);
  servoF.attach(pinF);

}

void loop() {
  servoA.write(openValue);
  servoB.write(openValue);
  servoC.write(openValue);
  servoD.write(openValue);
  servoE.write(openValue);
  servoF.write(openValue);
  
  delay(delayTime);

  servoA.write(closeValue);
  servoB.write(closeValue);
  servoC.write(closeValue);
  servoD.write(closeValue);
  servoE.write(closeValue);
  servoF.write(closeValue);

  delay(delayTime);
}
