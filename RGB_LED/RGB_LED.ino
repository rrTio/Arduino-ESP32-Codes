int ledRed= 5;
int ledGreen = 6;
int ledBlue = 7;

int delayTime = 250;

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
}

void loop() {
  RGB_color(255, 0, 0); // Red
  delay(delayTime);
  RGB_color(0, 255, 0); // Green
  delay(delayTime);
  RGB_color(0, 0, 255); // Blue
  delay(delayTime);
}

void RGB_color(int red, int green, int blue)
 {
  analogWrite(ledRed, red);
  analogWrite(ledGreen, green);
  analogWrite(ledBlue, blue);
}
