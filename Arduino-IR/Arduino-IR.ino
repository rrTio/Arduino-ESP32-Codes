int irLeft = 52;
int irRight = 53;

int in = 30;
int out = 32;
int value = 0;

void setup() {
  pinMode(irLeft, INPUT);
  pinMode(irRight, INPUT);
  pinMode(in, OUTPUT);
  pinMode(out, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  if(value == 0){
    if(digitalRead(irLeft) == 0){
      value = 1;
      digitalWrite(in, HIGH);
      digitalWrite(out, LOW);
      }
    }
    
  if(value == 1){
    if(digitalRead(irRight) == 0){
      value = 0;
      digitalWrite(in, LOW);
      digitalWrite(out, HIGH);
      }
    }
}
