 #include <WiFi.h>
#include <WebServer.h>

const char* ssid = "XeviousNet";  // Enter SSID here
const char* password = "xeviousNet";  //Enter Password here

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

uint8_t LED1pin = 27;
bool LED1status = LOW;

int infra = 26;
bool infraStatus;

int trig = 18;
int echo = 19;
long duration;
float centimeters, inches;

void setup() {
  Serial.begin(115200);
  pinMode(LED1pin, OUTPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  pinMode(infra, INPUT);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
  
  if(LED1status){
    digitalWrite(LED1pin, HIGH);
    }
  else{
    digitalWrite(LED1pin, LOW);
    }

  if(digitalRead(infra) == LOW){
    infraStatus = true;
    }
  if(digitalRead(infra) == HIGH){
    infraStatus = false;
    }
  //ULTRASONIC
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  centimeters = duration * 0.034/2;
  inches = centimeters / 2.54;
}

void handle_OnConnect() {
  LED1status = LOW;
  server.send(200, "text/html", SendHTML(LED1status, infraStatus, centimeters, inches)); 
}

void handle_led1on() {
  LED1status = HIGH;
  server.send(200, "text/html", SendHTML(true, infraStatus, centimeters, inches)); 
}

void handle_led1off() {
  LED1status = LOW;
  server.send(200, "text/html", SendHTML(false, infraStatus, centimeters, inches)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t led1stat, bool infrastat, float cm, float inch){
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
  ptr +="<h1>LED, IR, & ULTRASONIC</h1>\n";
  ptr +="<h3>WEB SERVER USING ESP32 ACCESS POINT</h3>\n";
  
  if(led1stat){
    ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";
  }
  else{
    ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";
  }

  if(infrastat){
    ptr +="<h3 class=\"irOn\">IR: 1</h3>\n";
  }
  else{
    ptr +="<h3 class=\"irOff\">IR: 0</h3>\n";
  }

  ptr +="<h3>ULTRASONIC</h3>\n";
  ptr +="<p>CENTIMETERS: ";
  ptr +=cm;
  ptr +="cm</p>\n";
  ptr +="<p>INCHES: ";
  ptr += inch; 
  ptr +="in</p>\n";
  
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
