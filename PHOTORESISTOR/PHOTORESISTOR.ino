void setup() {
  pinMode(A3, INPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}

void loop() {
 int value = analogRead(A3);
 Serial.println(value);
 analogWrite(8, map(value, 0, 1022, 0, 255));
 delay(1000);

}
