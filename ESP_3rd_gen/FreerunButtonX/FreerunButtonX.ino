/*
    This sketch sends a string to a TCP server, and prints a one-line response.
    You must run a TCP server in your local network.
    For example, on Linux you can use this command: nc -v -l 3000
*/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>


const char *ssid = "FreerunButtons";
const char *password = "freerunforrestfreerun";   

const char* host = "192.168.4.1";
const uint16_t port = 80 ; 

WiFiClient client;
String btnId = "unknown"; 


ESP8266WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(millis());
    Serial.print(".");
    delay(1000);
  }

  Serial.println("");
  Serial.print(millis());
  Serial.println(" - WiFi connected");
  Serial.println("IP address: ");
  IPAddress ipAdr = WiFi.localIP();
  btnId = ipAdr.toString();
  Serial.println(btnId);

  delay(500);
}



long SendRequest(long msec, String btnId, long previousResponseTime) 
{
  long startTime = millis();
  String url 
    = "/btn?msec="+ String(msec) 
      + "&sender="+btnId
      + "&prevdur="+previousResponseTime;
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
//  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: keep-alive\r\n\r\n");
  //read back one line from server
  String line = client.readStringUntil('\r');
  Serial.println("closing connection");
  client.stop();
  Serial.print("received from remote server [ ");
  Serial.print(line);
  Serial.println(" ]");
  return millis() - startTime;
}


long pressMoment = -1;
long previousRespTime = -1;



void loop() {
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    delay(5000);
    return;
  }
  
  pressMoment = millis();
  previousRespTime = SendRequest(pressMoment , btnId, previousRespTime);


  Serial.println("wait 1 sec...");
  delay(1000);
}
