#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32Xevious";
const char* password = "12345678";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

uint8_t irA = 27;
uint8_t irB = 26;
uint8_t irC = 25;
int count = 0;
int counter = 0;

int selectA, selectB, selectC, statA, statB, statC;
bool statusA, statusB, statusC;

int ledA = 19;
int ledB = 18;
int ledC = 17;

bool ledAStat = LOW;
bool ledBStat = LOW;
bool ledCStat = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(irA, INPUT);
  pinMode(irB, INPUT);
  pinMode(irC, INPUT);

  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledC, OUTPUT);
  
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", handle_OnConnect);
  server.on("/slotAO", handle_slotAO);
  server.on("/slotAO", handle_slotAV);
  server.on("/slotBO", handle_slotBO);
  server.on("/slotBC", handle_slotBV);
  server.on("/slotCO", handle_slotCO);
  server.on("/slotCV", handle_slotCV);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  selectA = digitalRead(irA);
  selectB = digitalRead(irB);
  selectC = digitalRead(irC);

  if(selectA == 1 && statA == 0){
    counter += 1;
    statA = 1;
    statusA = false;
    }
  else if(selectA == 0 && statA == 1){
    counter -= 1;
    statA = 0;
    statusA = true;
    }
    
  if(selectB == 1 && statB == 0){
    counter += 1;
    statB = 1;
    statusB = false;
    }
  else if(selectB == 0 && statB == 1){
    counter -= 1;
    statB = 0;
    statusB = true;
    }
    
  if(selectC == 1 && statC == 0){
    counter += 1;
    statC = 1;
    statusC = false;
    }
  else if(selectC == 0 && statC == 1){
    counter -= 1;
    statC = 0;
    statusC = true;
    }

  if(ledAStat){
    digitalWrite(ledA, HIGH);
    }
  else{
    digitalWrite(ledA, LOW);
    }
    
  if(ledBStat){
    digitalWrite(ledB, HIGH);
    }
  else{
    digitalWrite(ledB, LOW);
    }
    
  if(ledCStat){
    digitalWrite(ledC, HIGH);
    }
  else{
    digitalWrite(ledC, LOW);
    }
  count = counter;
  Serial.println(count);
}

void handle_OnConnect(){
  ledAStat = LOW;
  ledBStat = LOW;
  ledCStat = LOW;
  server.send(200, "text/html", SendHTML(statusA, statusB, statusC, count, ledAStat, ledBStat, ledCStat)); 
  Serial.println("IR A: " + statusA);
  Serial.println("IR B: " + statusB);
  Serial.println("IR C: " + statusC);
}

void handle_slotAO(){
  ledAStat = HIGH;
  server.send(200, "text/html", SendHTML(statusA, statusB, statusC, count, true, ledBStat, ledCStat));
  Serial.println("IR A: " + statusA);
  Serial.println("IR B: " + statusB);
  Serial.println("IR C: " + statusC);
  }

void handle_slotAV(){
  ledAStat = LOW;
  server.send(200, "text/html", SendHTML(statusA, statusB, statusC, count, false, ledBStat, ledCStat)); 
  Serial.println("IR A: " + statusA);
  Serial.println("IR B: " + statusB);
  Serial.println("IR C: " + statusC);
  }

void handle_slotBO(){
  ledBStat = HIGH;
  server.send(200, "text/html", SendHTML(statusA, statusB, statusC, count, ledAStat, true, ledCStat)); 
  Serial.println("IR A: " + statusA);
  Serial.println("IR B: " + statusB);
  Serial.println("IR C: " + statusC);
  }

void handle_slotBV(){
  ledBStat = LOW;
  server.send(200, "text/html", SendHTML(statusA, statusB, statusC, count, ledAStat, false, ledCStat)); 
  Serial.println("IR A: " + statusA);
  Serial.println("IR B: " + statusB);
  Serial.println("IR C: " + statusC);
  }

void handle_slotCO(){
  ledCStat = HIGH;
  server.send(200, "text/html", SendHTML(statusA, statusB, statusC, count, ledAStat, ledBStat, true)); 
  Serial.println("IR A: " + statusA);
  Serial.println("IR B: " + statusB);
  Serial.println("IR C: " + statusC);
  }

void handle_slotCV(){
  ledCStat = LOW;
  server.send(200, "text/html", SendHTML(statusA, statusB, statusC, count, ledAStat, ledBStat, false)); 
  Serial.println("IR A: " + statusA);
  Serial.println("IR B: " + statusB);
  Serial.println("IR C: " + statusC);
  }

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(bool statA, bool statB, bool statC, int counts, uint8_t ledstatA, uint8_t ledstatB, uint8_t ledstatC){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" http-equiv=\"refresh\" content=\" 1\" width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>PARKING LOT SYSTEM</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #000000;margin: 50px auto 30px;} h3 {color: #000000;margin-bottom: 50px;}\n";
  ptr +="p {font-size: 34px;font-weight: 800;color: #000000;margin-top: 25px; margin-bottom: 10px;}\n";
  ptr +=".slot-occupied{border: 5px solid red; background: red; color: white;}";
  ptr +=".slot-vacant{border: 5px solid green; background: green; color: black;}";
  ptr +="</style>\n";
  
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>PARKING LOT SYSTEM</h1>\n";
  ptr +="<h3>WEB SERVER USING ESP32 ACCESS POINT</h3>\n";

  ptr += "<p>VACANT: ";
  ptr += counts;
  ptr += "</p>\n";

  if(statA){
    ptr +="<p class=\"slot slot-occupied\">SLOT A: OCCUPIED</p> <a href=\"/slotAO\"></a>\n";
  }
  else{
    ptr +="<p class=\"slot slot-vacant\">SLOT A: VACANT</p> <a href=\"/slotAV\"> </a>\n";
  }
  
  if(statB){
    ptr +="<p class=\"slot slot-occupied\">SLOT B: OCCUPIED</p> <a href=\"/slotBO\"> </a>\n";
  }
  else{
    ptr +="<p class=\"slot slot-vacant\">SLOT B: VACANT</p> <a href=\"/slotBV\"> </a>\n";
  }
  
  if(statC){
    ptr +="<p class=\"slot slot-occupied\">SLOT C: OCCUPIED</p> <a href=\"/slotCO\"> </a>\n";
  }
  else{
    ptr +="<p class=\"slot slot-vacant\">SLOT C: VACANT</p> <a href=\"/slotCV\"> </a>\n";
  }
  
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
