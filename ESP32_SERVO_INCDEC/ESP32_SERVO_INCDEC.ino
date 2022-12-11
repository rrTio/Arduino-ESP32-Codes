#include <ESP32Servo.h>
Servo servoA, servoB, servoC, servoD, servoE, servoF;

int delayTime = 500;
int pinA = 27;
int pinB = 26;
int pinC = 25;
int pinD = 33;
int pinE = 32;
int pinF = 35;

int trigA = 19;
int echoA = 18;

int trigB = 17;
int echoB = 16;

long durationA, durationB;
int distanceA, distanceB;
float cmA, inA, cmB, inB;

void setup() {
  servoA.attach(pinA);
  servoB.attach(pinB);
  servoC.attach(pinC);
  servoD.attach(pinD);
  servoE.attach(pinE);
  servoF.attach(pinF);

  pinMode(trigA, OUTPUT);
  pinMode(trigB, OUTPUT);
  pinMode(echoA, INPUT);
  pinMode(echoB, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigA, LOW);
  delayMicroseconds(2);
  digitalWrite(trigA, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigA, LOW);
  durationA = pulseIn(echoA, HIGH);
  cmA = durationA * 0.034/2;
  inA = cmA / 2.54;

  digitalWrite(trigB, LOW);
  delayMicroseconds(2);
  digitalWrite(trigB, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigB, LOW);
  durationB = pulseIn(echoB, HIGH);
  cmB = durationB * 0.034/2;
  inB = cmB / 2.54;

  Serial.print("Centimeters A: ");
  Serial.println(cmA);
  Serial.print("Inches B: ");
  Serial.println(inA);

  Serial.print("Centimeters B: ");
  Serial.println(cmB);
  Serial.print("Inches B: ");
  Serial.println(inB);
}

void openServo(){}

void closeServo(){}
