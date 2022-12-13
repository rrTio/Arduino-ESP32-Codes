#include <ESP32Servo.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "XeviousNet";
const char* password = "xeviousNet";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

Servo servoA, servoB, servoC, servoD, servoE, servoF;

int delayTime = 500;
int pinA = 27;
int pinB = 26;
int pinC = 25;
int pinD = 33;
int pinE = 32;
int pinF = 35;

int openValue = 90;
int closeValue = 0;

//OUTSIDE DETECTOR
int trigA = 19;
int echoA = 18;

//INSIDE DETECTOR
int trigB = 17;
int echoB = 16;

long durationA, durationB;
int distanceA, distanceB;
float cmA, inA, cmB, inB;

int state = 0;

void setup() {
  Serial.begin(115200);
  servoA.attach(pinA);
  servoB.attach(pinB);
  servoC.attach(pinC);
  servoD.attach(pinD);
  servoE.attach(pinE);
  servoF.attach(pinF);
  
  pinMode(trigA, OUTPUT);
  pinMode(echoA, INPUT);

  pinMode(trigB, OUTPUT);
  pinMode(echoB, INPUT);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  
  digitalWrite(trigA, LOW);
  delayMicroseconds(2);
  digitalWrite(trigA, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigA, LOW);
  durationA = pulseIn(echoA, HIGH);
  cmA = durationA * 0.034/2;
  inA = cmA / 2.54;

  digitalWrite(trigB, LOW);
  delayMicroseconds(2);
  digitalWrite(trigB, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigB, LOW);
  durationB = pulseIn(echoB, HIGH);
  cmB = durationB * 0.034/2;
  inB = cmB / 2.54;

  Serial.print("Centimeters A: ");
  Serial.println(cmA);
  Serial.print("Inches B: ");
  Serial.println(inA);

  Serial.print("Centimeters B: ");
  Serial.println(cmB);
  Serial.print("Inches B: ");
  Serial.println(inB);

  if(cmA < 20){
    openServo();
    delay(delayTime);
    closeServo();
    delay(delayTime);
    }

  if(cmB <20){
    openServo();
    state = 1;
    }
  else{
    closeServo();
    state = 0;
    }
}

void openServo(){
  servoA.write(openValue);
  servoB.write(openValue);
  servoC.write(openValue);
  servoD.write(openValue);
  servoE.write(openValue);
  servoF.write(openValue);
  }

void closeServo(){
  servoA.write(closeValue);
  servoB.write(closeValue);
  servoC.write(closeValue);
  servoD.write(closeValue);
  servoE.write(closeValue);
  servoF.write(closeValue);
  }

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML(cmA, inA, cmB, inB, state)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float centA, float inchA, float centB, float inchB, int stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" http-equiv=\"refresh\" content=\" 2\" width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED, IR, & ULTRASONIC</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +=".irOn{display: block;width: 80px;background:green; color:white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;}\n";
  ptr +=".irOff{display: block;width: 80px;background:red; color:black;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;}\n";
  ptr +="p {font-size: 14px;color: black;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h3>WEB SERVER USING ESP32 ACCESS POINT</h3>\n";
  
  ptr +="<h3>ULTRASONIC A</h3>\n";
  ptr +="<p>CENTIMETERS: ";
  ptr +=centA;
  ptr +="cm</p>\n";
  ptr +="<p>INCHES: ";
  ptr += inchA; 
  ptr +="in</p>\n\n";

  ptr +="<h3>ULTRASONIC B</h3>\n";
  ptr +="<p>CENTIMETERS: ";
  ptr +=centB;
  ptr +="cm</p>\n";
  ptr +="<p>INCHES: ";
  ptr += inchB; 
  ptr +="in</p>\n\n";

  if(stat = 1){
    ptr +="<p>BIN IS FULL</p>\n";
    }
    
  if(stat = 0){
    ptr +="<p>BIN IS NOT FULL</p>\n";
    }
  
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
