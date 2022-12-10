int led = 8;
int i;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  for(i = 0; i <= 255; i++)
    {
      analogWrite(led, i);
      Serial.println(i);
      delay(10);
    }
    
  for(i = 255; i >= 0; i--)
    {
      analogWrite(led, i);
      Serial.println(i);
      delay(10);
    }
}
