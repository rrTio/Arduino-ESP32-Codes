int ena = 7;
int in1 = 6;
int in2 = 5;

void setup() {
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {
  analogWrite(ena, 100);
  forward();
  delay(5000);
  
  analogWrite(ena, 255);
  backward();
  delay(5000);
}

void forward()
  {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  }

void backward()
  {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  }
  
