//ULTRASONIC SENSOR
int trig = 9;
int echo = 10;
long duration;
int distance;
float centimeters, inches;

void setup() {
  //ULTRASONIC SENSOR
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  Serial.begin(9600);
}

void loop() {

  //ULTRASONIC
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  centimeters = duration * 0.034/2;
  inches = centimeters / 2.54;
  
  Serial.print("Centimeters: ");
  Serial.println(centimeters);
  Serial.print("Inches: ");
  Serial.println(inches);
}
