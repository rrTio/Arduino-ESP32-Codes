int piezo = 2;

int i;
int delayTime = 1;

void setup() {
  pinMode(piezo, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  for(i = 0; i <= 1000; i++){
    tone(piezo, i);
    delay(delayTime);
    }
  
  for(i = 1000; i >= 0; i--){
    tone(piezo, i);
    delay(delayTime);
    }
}
