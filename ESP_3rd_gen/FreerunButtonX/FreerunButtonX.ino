/*
    This sketch sends a string to a TCP server, and prints a one-line response.
    You must run a TCP server in your local network.
    For example, on Linux you can use this command: nc -v -l 3000
*/
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#else
#include <WiFi.h>
#endif



// ------  network stuff... --------------------------
  const char *ssid = "FreerunButtons";
  const char *password = "freerunforrestfreerun";   

  const char* host = "192.168.4.1";   // base-ESP will get up at this IP. 
  const uint16_t port = 80 ; 

  WiFiClient client;
  ESP8266WiFiMulti WiFiMulti;
  String btnId =  "-";  
  String ip;
  

// ------  button / timing stuff --------------------------
  int inputPin = D3;  // pushbutton connected to digital pin D3
  bool isLedOn = false;
  long pressMoment = -1;
  long previousRespTime = -1;


// ------  functionality --------------------------

bool isButtonDownNow() {
  return LOW == digitalRead(inputPin);
}


void setLed(bool switchTo) 
{
    digitalWrite(LED_BUILTIN, switchTo ? HIGH : LOW);  
}

void EnsureButtonIdIsSet() 
{
  if (btnId == "-") 
  {
    btnId = String(random(1000000));
  }
}

// return: responseTime
long SendRequest(long msec, String btnId, long previousResponseTime) 
{
  long startTime = millis();
  EnsureButtonIdIsSet();
  String url = "/btn?msec="+ String(msec) 
                + "&sender="+btnId
                + "&prevdur="+previousResponseTime
                + "&ip="+ip;
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  //  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: keep-alive\r\n\r\n");
  //read back one line from server
  String line = client.readStringUntil('\r');
//  String line2 = client.readStringUntil('\r');  // when these readStrings are commented out a request takes around 10 msec, 
//  String line3 = client.readStringUntil('\r');  // otherwise 5000 msec. (the returning info is in 'line6', but we don't need that per se). 
//  String line4 = client.readStringUntil('\r');
//  String line5 = client.readStringUntil('\r');
//  String line6 = client.readStringUntil('\r');
  Serial.println("closing connection");
  client.stop();
  Serial.print("received from remote server [ ");
//  Serial.print(line);
//  Serial.print(" ]-[ ");
//  Serial.print(line2);  
//  Serial.print(" ]--[");
//  Serial.print(line3);  
//  Serial.print(" ]---[");
//  Serial.print(line4);  
//  Serial.print(" ]---[");
//  Serial.print(line5);  
//  Serial.print(" ]---[");
//  Serial.print(line6);  
  Serial.println(" ]");
  return millis() - startTime;   // responseTime will be sent to server with next request! 
}


void connectToNetwork() {
  isLedOn = true;
  setLed(isLedOn);
  Serial.print("Wait for WiFi... ");
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  while (WiFiMulti.run() != WL_CONNECTED) {
    setLed(isLedOn );
    
    isLedOn = ! isLedOn;
    Serial.print(millis());
    Serial.print(".");
    delay(5000);
  }
  int blinkTime = 500;
  // blink faster and faster to signal that network is connected
  while (blinkTime > 0) {
    delay(blinkTime);
    setLed(false);
    delay(blinkTime);
    setLed(true);
    blinkTime = blinkTime - 25;
    Serial.print(" - WiFi connected -> ");
    Serial.println(millis());
  }
}


// ------  setup --------------------------
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("---------------------------------------------------------------------");
  Serial.println("--- SETUP ---");

    // initialize i/o
  pinMode(LED_BUILTIN, OUTPUT);   
  setLed(false);
  pinMode(inputPin, INPUT);  
  
  connectToNetwork();  
  IPAddress ipAdr = WiFi.localIP();
  ip = ipAdr.toString();
  Serial.println(btnId);
  Serial.print("connecting to " + String(host) + ":" + String(port));

  delay(500);
}


// ------  loop --------------------------
void loop() {
  if (isButtonDownNow())
  {
    pressMoment = millis();
    if (!client.connect(host, port)) {
      Serial.println("connection failed");
      Serial.println("*");
      delay(1000);
      return;
    }
    previousRespTime = SendRequest(pressMoment , btnId, previousRespTime);
    Serial.print("<< DOWN >>");    
    delay(2000);
  } 
}
