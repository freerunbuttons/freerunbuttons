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

int lastContactMsec = 0; 


void handleRoot() {
  
  server.send(200, "text/html","<h1>You are connected</h1>");
  Serial.print("X");
}

void prn(String name, String value) {
  Serial.print(" "+name+": ");
  Serial.print(value); 
}

void handleBtn() {
  long serverMsec = millis();
  String clientMsec = server.arg("msec");
  String clientId  = server.arg("sender");
  String previousResponseTime = server.arg("prevdur");
  server.send(200, "text/plain", "a b c.");
  Serial.print("--> ");
  prn( "Sender", clientId);
  prn("previousRequestDuration", previousResponseTime);
  prn("client", clientMsec );
  prn("server", String(serverMsec) );
  long offset = serverMsec - atol(clientMsec.c_str());
  prn("offset", String(offset) );
  Serial.println();
  lastContactMsec = serverMsec;
}


void setup()
{
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Setting soft-AP ... ");
 
  boolean result = WiFi.softAP(ssid, password);
  if(result)
  {
    Serial.print("- SoftAP is Ready: ");
    Serial.println(ssid);
    Serial.print("-              IP: ");
    Serial.println(WiFi.softAPIP());
    server.on("/", handleRoot);
    server.on("/btn", handleBtn);
    server.begin();
    Serial.println("HTTP server started");
  }
  else
  {
    Serial.println("- Setting up Soft Access Point Failed!");
  }
}



int count = 0;
int numsoftAPConnectedStations = -1;


bool isLongerThanXSecondsApart(long moment1, long moment2, long seconds) {
  long duration = moment1 < moment2  ?  moment2 - moment1  :  moment1 - moment2 ;
  return duration > 1000 * seconds ;  
}

void loop()
{
  server.handleClient();
  ++count;
  if (count % 1000000 == 0) 
  { 
    // WiFi.softAPgetStationNum() changes ? Then print! 
    int num = WiFi.softAPgetStationNum();
    if  (num != numsoftAPConnectedStations || isLongerThanXSecondsApart(lastContactMsec, millis(), 60) ) 
    {
      numsoftAPConnectedStations = num;
      lastContactMsec = millis();
      Serial.println();
      Serial.print(" --- IDLE at: "+ millis());
      Serial.printf(" stationsConnected: %d\n", num);
    }
  }
}
