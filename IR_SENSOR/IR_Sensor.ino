//IR SENSOR
int irSensor = 5;

//LED
int ledLight = 13;
int led = 50;

void setup() {
  //IR SENSOR
  pinMode(irSensor, INPUT);
  pinMode(ledLight, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  //IR SENSOR
  if(digitalRead(irSensor) == HIGH){
    Serial.print("IR HIGH\n");
    
    digitalWrite(led, LOW);
    digitalWrite(ledLight, HIGH);
    }
    
  if(digitalRead(irSensor) == LOW){
    Serial.print("IR LOW\n");
    
    digitalWrite(ledLight, LOW);
    digitalWrite(led, HIGH);
    }

}
