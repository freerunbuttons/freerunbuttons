/*
    This sketch sends a string to a TCP server, and prints a one-line response.
    You must run a TCP server in your local network.
    For example, on Linux you can use this command: nc -v -l 3000
*/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>


// ------  network stuff... --------------------------
  const char *ssid = "FreerunButtons";
  const char *password = "freerunforrestfreerun";   

  const char* host = "192.168.4.1";   // base-ESP will get up at this IP. 
  const uint16_t port = 80 ; 

  WiFiClient client;
  String btnId = "unknown"; 
  ESP8266WiFiMulti WiFiMulti;


// ------  button / timing stuff --------------------------
  int inputPin = D3;  // pushbutton connected to digital pin D3
  int val = 0;        // variable to store the read value

  long pressMoment = -1;
  long previousRespTime = -1;


// ------  functionality --------------------------
// return: responseTime
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


void connectToNetwork() {
  val = HIGH;
  digitalWrite(LED_BUILTIN, HIGH); 
//-----
  Serial.print("Wait for WiFi... ");
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  while (WiFiMulti.run() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, val);  
    val = 1 - val;
    Serial.print(millis());
    Serial.print(".");
    delay(5000);
  }
  int blinkTime = 500;
  // blink faster and faster to signal that network is connected
  while (blinkTime > 0) {
    delay(blinkTime);
    digitalWrite(LED_BUILTIN, LOW);  
    delay(blinkTime);
    digitalWrite(LED_BUILTIN, HIGH);  
    blinkTime = blinkTime - 25;
    Serial.print(" - WiFi connected -> ");
    Serial.println(millis());
  }
}

bool isButtonDownNow() {
  return LOW == digitalRead(inputPin);
}


// ------  setup --------------------------
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("---------------------------------------------------------------------");
  Serial.println("--- SETUP ---");

    // initialize i/o
  pinMode(LED_BUILTIN, OUTPUT);   
  pinMode(inputPin, INPUT);  
  digitalWrite(LED_BUILTIN, LOW);  

  connectToNetwork();  
  IPAddress ipAdr = WiFi.localIP();
  btnId = ipAdr.toString();
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
