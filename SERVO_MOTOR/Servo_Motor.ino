//SERVO MOTOR
#include <Servo.h>
Servo servoMotor;

void setup() {
  servoMotor.attach(4);
  Serial.begin(9600);
}

void loop() {
  servoMotor.write(45);
  delay(500);
  servoMotor.write(90);
  delay(500);
  servoMotor.write(135);
  delay(500);
  servoMotor.write(180);
  delay(500);
  servoMotor.write(135);
  delay(500);
  servoMotor.write(90);
  delay(500);
  servoMotor.write(45);
  delay(500);
  servoMotor.write(0);
  delay(500);

}
