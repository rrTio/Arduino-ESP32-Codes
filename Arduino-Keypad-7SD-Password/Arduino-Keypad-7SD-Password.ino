#include <Keypad.h>

int pinA = 31;
int pinB = 33;
int pinC = 35;
int pinD = 37;
int pinE = 39;
int pinF = 41;
int pinG = 43;

int ledB = 48;
int ledR = 44;

int irLeft = 50;
int irRight = 52;

int in = 12;
int out = 13;
int value = 0;

int delayTime = 250;

const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
  };

byte rowPins[rows] = {9,8,7,6};
byte colPins[cols] = {5,4,3,2};

const String password = "1243";
String result;
String typePass;

Keypad keyPressed = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void setup() {
 Serial.begin(9600);

 pinMode(pinA, OUTPUT);
 pinMode(pinB, OUTPUT);
 pinMode(pinC, OUTPUT);
 pinMode(pinD, OUTPUT);
 pinMode(pinE, OUTPUT);
 pinMode(pinF, OUTPUT);
 pinMode(pinG, OUTPUT);
 pinMode(ledB, OUTPUT);
 pinMode(ledR, OUTPUT);

 pinMode(irLeft, INPUT);
 pinMode(irRight, INPUT);
 pinMode(in, OUTPUT);
 pinMode(out, OUTPUT);
}

void loop() {
  char customKey = keyPressed.getKey();

  if(customKey)
  {
    Serial.print(customKey);
    
    if(customKey == '*'){
    typePass = "";
    Serial.println("CLEAR");
    }
    else if(customKey == '#')
    {
      if(password == typePass)
      {
        result = "CORRECT";
        Serial.println("\nPASSWORD: " + password);
        Serial.println("TYPED PASSWORD: " + typePass);
        Serial.println("RESULT: " + result);

        off();
        digitalWrite(ledB, HIGH);
        delay(delayTime);
        digitalWrite(ledB, LOW);
        delay(delayTime);
        digitalWrite(ledB, HIGH);
        delay(delayTime);
        digitalWrite(ledB, LOW);
        delay(delayTime);
        digitalWrite(ledB, HIGH);
        delay(delayTime);
        digitalWrite(ledB, LOW);
      }
      
      else
      {
        result = "INCORRECT";
        Serial.println("\nPASSWORD: " + password);
        Serial.println("TYPED PASSWORD: " + typePass);
        Serial.println("RESULT: " + result);
        
        digitalWrite(ledR, HIGH);
        delay(delayTime);
        digitalWrite(ledR, LOW);
        delay(delayTime);
        digitalWrite(ledR, HIGH);
        delay(delayTime);
        digitalWrite(ledR, LOW);
        delay(delayTime);
        digitalWrite(ledR, HIGH);
        delay(delayTime);
        digitalWrite(ledR, LOW);
        off();
      }
      typePass = "";
    }
    else
    {
      typePass += customKey;
    }
  }

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

  if(customKey == '1'){
    one();
    }
  if(customKey == '2'){
    two();
    }
  if(customKey == '3'){
    three();
    }
  if(customKey == '4'){
    four();
    }
  if(customKey == '5'){
    five();
    }
  if(customKey == '6'){
    six();
    }
  if(customKey == '7'){
    seven();
    }
  if(customKey == '8'){
    eight();
    }
  if(customKey == '9'){
    nine();
    }
  if(customKey == '0'){
    zero();
    }
}

//SEVEN SEGMENT DISPLAY
void one(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
  }
  
void two(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
  }
  
void three(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH); 
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
  }
  
void four(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  }
  
void five(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  }
  
void six(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  }
  
void seven(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, HIGH);
  }
void eight(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  }
  
void nine(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH);
  }
  
void zero(){
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH);
  digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH);
  digitalWrite(pinF, HIGH);
  digitalWrite(pinG, LOW);
}

void off(){
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW);
  digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW);
}
