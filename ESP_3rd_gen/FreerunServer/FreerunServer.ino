#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h> 


// Soft Access Point: 
// https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-examples.html
//
// WiFiAccessPoint: 
// https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiAccessPoint/WiFiAccessPoint.ino



const char *ssid = "FreerunButtons";
// passwd must have length >= 8 : https://github.com/esp8266/Arduino/issues/1141
const char *password = "freerunforrestfreerun";   

ESP8266WebServer server(80); 


void handleRoot() {
  server.send(200, "text/html","<h1>You are connected</h1>");
}


void setup()
{
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Setting soft-AP ... ");
 
  boolean result = WiFi.softAP(ssid, password);
  if(result)
  {
    Serial.print("- SoftAP is Ready: ");
    Serial.println(ssid);
    Serial.print("-              IP: ");
    Serial.println(WiFi.softAPIP());
    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP server started");
  }
  else
  {
    Serial.println("- Setting up Soft Access Point Failed!");
  }
}



void loop()
{
  server.handleClient();
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(3000);
}
