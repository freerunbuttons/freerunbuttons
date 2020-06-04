#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);
#else
#include <WiFi.h>             
#include <WiFiClient.h>
#include <WebServer.h>
WebServer server(80);
#endif

// Soft Access Point:
// https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-examples.html
//
// WiFiAccessPoint:
// https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiAccessPoint/WiFiAccessPoint.ino
//
// Porting to ESP32
// https://github.com/zhouhan0126/WebServer-esp32/blob/master/examples/HelloServer/HelloServer.ino



const char *ssid = "FreerunButtons";
// passwd must have length >= 8 : https://github.com/esp8266/Arduino/issues/1141
const char *password = "freerunforrestfreerun";



int lastContactMsec = 0;


const int numberOfButtons = 3;
const int bufferSize = numberOfButtons * 10;
long pressedStore [bufferSize];  // circular array, 'crsr' pointing to next free cel.
int crsr = 0;


void clearStore()
{
  for(int i=0 ; i < bufferSize ; ++i )
  {
    pressedStore[i] = 0;
  }
}


void addPress(long timeOfPress)
{
  pressedStore[crsr] = timeOfPress ;         // not yet very precise...
  ++crsr;
}


//  pressedStore[i] = 0;  // fake time to begin with.
//  pressedStore[i] = 0;  // fake time to begin with.
//  pressedStore[i] = 0;  // fake time to begin with.


void showStore()
{
  Serial.println();
  for(int i=0 ; i < bufferSize ; ++i )
  {
    if (i == crsr) { Serial.print(" [[[ "); }
    Serial.print(pressedStore[i]);
    if (i == crsr) { Serial.print(" ]]] "); }
    Serial.print(".");
  }
  Serial.println();
}



void handleRoot() {

  server.send(200, "text/html","<h1>You are connected</h1>");
  Serial.print("X");
}


void prn(String name, String value) {
  Serial.print(" "+name+": ");
  Serial.print(value);
}


void showTimes()
{
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println("---------------------------------------------");
  Serial.println();
  int t1Index = ((crsr - 1) / 3) * 3;
  long t1 = pressedStore[ t1Index ];
  long t2 = pressedStore[ t1Index + 1 ];
  long t3 = pressedStore[ t1Index + 2 ];
  long halfTime = t2 - t1;
  long endTime  = t3 - t1;
//  prn("crsr", String(crsr));
//  Serial.println();
//  prn("t1Index", String(t1Index));
//  Serial.println();
  switch( crsr % 3 ) {
    case 1:
              Serial.println("-- Started --");
              break;
    case 2:
              prn("Halftime   ", String( halfTime ));
              Serial.println();
              break;
    case 0:
              prn("Halftime   ", String( halfTime ));
              Serial.println();
              prn("Endtime    ", String( endTime ));
              Serial.println();
              break;
  }
  Serial.println("---------------------------------------------");
  Serial.println();
  Serial.println();
  Serial.println();
}


void handleBtn() {
  long serverMsec = millis();
  String clientMsecAsString = server.arg("msec");
  long   clientMsec = atol(clientMsecAsString.c_str());
  String clientId  = server.arg("sender");
  String previousResponseTime = server.arg("prevdur");
  String buttonIP = server.arg("ip");
  server.send(200, "text/plain", "a b c.");
  Serial.print("--> ButtonPress ");
  prn( "button", clientId);
  prn("previousRequestDuration", previousResponseTime);
  prn("clientTime", clientMsecAsString );
  prn("serverTime", String(serverMsec) );
  long offset = serverMsec - clientMsec;
  prn("offset", String(offset) );
  prn("buttonIP", buttonIP );
  Serial.println();
  lastContactMsec = serverMsec;
  long serverTimeOfPress = clientMsec + offset;
  addPress(serverTimeOfPress);
  showTimes();
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
    Serial.println("- Setting up Soft Access Point Failed! ----- PLEASE RESTART -----");
  }
  clearStore();
  addPress(1);  // fake data to test with...
  addPress(3);  // fake data to test with...
  addPress(8);  // fake data to test with...
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
      showStore();
      showTimes();
    }
  }
}
