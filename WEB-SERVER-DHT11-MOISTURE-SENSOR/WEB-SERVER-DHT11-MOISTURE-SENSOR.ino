#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

const char* ssid = "XeviousNet";
const char* password = "xeviousnet";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

uint8_t dhtPin = 26;
#define DHTTYPE DHT11
DHT dht(dhtPin, DHTTYPE);

int moistureSensor = 36; 
int limit = 300; 

float humidity, temperature, pHumidity, pTemperature;
int moisture, pMoisture;
 
void setup(){
 
  Serial.begin(115200);
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  pinMode(dhtPin, INPUT);
  pinMode(moistureSensor, INPUT); 
  dht.begin();

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(){
    server.handleClient();
    pMoisture = map(analogRead(moistureSensor), 100, 4095, 100, 0); 
    pTemperature = dht.readTemperature();
    pHumidity = dht.readHumidity();
    
    moisture = map(analogRead(moistureSensor), 100, 4095, 100, 0); 
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();
        
    Serial.print("Moisture: ");
    Serial.println(moisture);     
    Serial.print("humidity: ");
    Serial.print(humidity);
    Serial.println("%");
    Serial.print("temperature: ");
    Serial.print(temperature); 
    Serial.println("C");

    delay(500);
}

void handle_OnConnect(){
  server.send(200, "text/html", SendHTML(moisture, humidity, temperature, pMoisture, pHumidity, pTemperature));
}
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float moist, float humid, float temp, float pMoist, float pHumid, float pTemp){

  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" http-equiv=\"refresh\" content=\" 1\" width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>DHT11 & MOISTURE SENSOR</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #000000;margin: 50px auto 30px;} h3 {color: #000000;margin-bottom: 50px;}\n";
  ptr +="p {font-size: 34px;font-weight: 800;color: #000000;margin-top: 25px; margin-bottom: 10px;}\n";
  ptr +=".previous{margin-bottom:45px;}\n";
  ptr +="</style>\n";
  
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>DHT 11 & MOISTURE SENSOR</h1>\n";
  ptr +="<h3>WEB SERVER USING ESP32 ACCESS POINT</h3>\n";
  ptr +="<h2>READINGS</h2>\n";

  ptr += "<progress value=\"";
  ptr += temp;
  ptr += "\" max=\"100\">";
  ptr += "</progress>";
  ptr += "<h2>TEMPERATURE: ";
  ptr += temp;
  ptr += "</h2>\n";
  ptr += "<h4 class=\"previous\">PREVIOUS TEMPERATURE: ";
  ptr += pTemp;
  ptr += "</h4>\n\n\n";

  ptr += "<progress value=\"";
  ptr += humid;
  ptr += "\" max=\"100\">";
  ptr += "</progress>";
  ptr +="<h2>HUMIDITY: ";
  ptr += humid;
  ptr +="</h2>\n";
  ptr +="<h4 class=\"previous\">PREVIOUS HUMIDITY: ";
  ptr += pHumid;
  ptr +="</h4>\n\n\n";

  ptr +="<h2>MOISTURE LEVEL: ";
  ptr += moist;
  ptr +="</h2>\n";

  ptr +="<h4 class=\"previous\">PREVIOUS MOISTURE LEVEL: ";
  ptr +=pMoist;
  ptr +="</h4>\n";
    
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
