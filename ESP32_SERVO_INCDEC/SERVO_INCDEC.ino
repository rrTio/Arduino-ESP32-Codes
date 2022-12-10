#include <ESP32Servo.h>
Servo servoMotor;

int i;
int value = 0;
int delayTime = 5;
int servoPin = 26;
void setup() {
  servoMotor.attach(servoPin);
  Serial.begin(9600);

}

void loop() {
  servoMotor.write(180);
  delay(500);
  servoMotor.write(0);
  delay(500);
}
