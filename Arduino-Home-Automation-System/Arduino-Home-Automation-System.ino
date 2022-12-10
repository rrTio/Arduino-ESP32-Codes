//SERVO MOTOR
#include <Servo.h>
Servo servoMotor;
int servo = 8;

//ULTRASONIC SENSOR
int trig = 9;
int echo = 10;
long duration;
int distance;
float centimeters, inches;

//TEMPERATURE SENSOR
int temp = 7;
float temperature;

//DC MOTOR
int enA = 6;
int in1 = 5;
int in2 = 4;

//PIR
int pir = 3;
int state = LOW;
int val = 0;

//PIEZO
int piezo = 11; 
int piezoTone = 800;

//LEDs
int red = A0;
int green = A1;
int blue = A2;

int led1 = 52;
int led2 = 50;
int led3 = 48;

//PHOTORESISTOR
int photoresistor = A3;
int lightValue;

void setup() {
  //ULTRASONIC SENSOR
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  //SERVO MOTOR
  servoMotor.attach(servo);

  //TEMPERATURE SENSOR
  pinMode(temp, INPUT);

  //DC MOTOR
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  //LED
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  //PIR
  pinMode(pir, INPUT);

  //PIEZO
  pinMode(piezo, OUTPUT);

  //PHOTORESISTOR
  pinMode(photoresistor, INPUT);
  
  Serial.begin(9600);
}

void loop() 
{
  //A
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  centimeters = duration * 0.034/2;
  inches = centimeters / 2.54;
  
  Serial.print("Centimeters: ");
  Serial.print(centimeters);
  Serial.print("\nInches: ");
  Serial.print(inches);

  //B
  val = digitalRead(pir);

  //C
  temperature = analogRead(temp);
  temperature = temperature * 0.48828125;

  //D
  int lightValue = analogRead(photoresistor);

  if(centimeters <= 40)
    {
      servoMotor.write(90);
      delay(2000);
      servoMotor.write(0);
    }
  else
    {
      servoMotor.write(0);
    }

  if(val == HIGH)
    {
      if(state == LOW)
        {
          tone(piezo, piezoTone);
          delay(3000);
          noTone(piezo);
          delay(1000);
          state = HIGH;
        }
    }
    
  else
    {
      noTone(piezo);
      if(state == HIGH)
        {
          state = LOW;
        }
    }
  
  if(temperature > 24)
    {
    analogWrite(enA, 255);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
    }
    
  if(temperature >= 20 && temperature <= 24)
    {
    analogWrite(enA, 125);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
    }
    
  if(temperature < 20)
    {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, HIGH);
    }

  Serial.print("\nTEMPERATURE: ");
  Serial.print(temperature);
  Serial.print("°C");
  Serial.println();

  
  tripleLight(lightValue, lightValue, lightValue);
  Serial.print("LIGHT: ");
  Serial.print(lightValue);
  Serial.println();
}

void tripleLight(int left, int mid, int right)
{
  analogWrite(led1, left);
  analogWrite(led2, mid);
  analogWrite(led3, right);  
}
