/* 
  int random_value;
  bool led_red;
  bool led_green;
  bool led_blue;
*/

#include "thingProperties.h"

int red = 25;
int green = 26;
int blue = 27;

void setup() {
  Serial.begin(9600);
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  ArduinoCloud.update();
  random_value = random(0, 500);
  delay(500);
  
}

void onLedRedChange()  {
  if(led_red){
    digitalWrite(red, HIGH);
  }
  else{
    digitalWrite(red, LOW);
  }
}

void onLedGreenChange()  {
  if(led_green){
    digitalWrite(green, HIGH);
  }
  else{
    digitalWrite(green, LOW);
  }
}

void onLedBlueChange()  {
  if(led_blue){
    digitalWrite(blue, HIGH);
  }
  else{
    digitalWrite(blue, LOW);
  }
}
