/*
  Laces_Coens 

  // Coen's variation on Laces_button, in setup sync time, in loop detect button press on 'D3': use builtin led and send ID+timestamp to a server. 
  
  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

//#include <ArduinoJson.h>
#include <ezTime.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <WiFiClient.h>
//#include <ESP8266HTTPClient.h>


const char* ssid = "KBnetwork"; //Enter SSID
const char* password = "0A0b0c0d0f"; //Enter Password

int inputPin = D3;  // pushbutton connected to digital pin D3
int val = 0;        // variable to store the read value

// Module Name : button ID
const char* moduleName = "MODULE00003";

const uint16_t port = 34005;
const char* server_ip = "192.168.1.26";

// ezTime
Timezone Netherlands; 



WiFiClient client;


// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid, password); 
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  //Initialize pushbuttons as inputs;
  pinMode(inputPin, INPUT);      // set pin as input

  connectToNetwork();
  Netherlands.setPosix("CET-1CEST,M3.5.0/2,M10.5.0/3"); 
//  setServer(server_ip+":"+port+"/ntp");  
//  waitForSync();
}



void loop() {
  
  val = digitalRead(inputPin); 
  digitalWrite(LED_BUILTIN, val);  

  if (val == LOW) {
    
    SendTimeStamp(Netherlands.dateTime("H_i_s_v"),WiFi.macAddress());
    delay(5000);    
  }

}



bool SendTimeStamp(String timestamp, String deviceId) {
  if (!client.connect(server_ip,port)) {
    return false;   
  }
  
  client.println("GET /examples/btn/"+deviceId+"/time/"+timestamp+" HTTP/1.1");
  client.print("Host: ");
  client.println(server_ip);
  client.println("Connection: close");
  client.println();
  return true;
}



void   connectToNetwork() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(LED_BUILTIN, val);  
    val = 1 - val;
    Serial.print("*");
  }
  int blinkTime = 500;
  // blink faster and faster to signal that network is connected
  while (blinkTime > 0) {
    delay(blinkTime);
    digitalWrite(LED_BUILTIN, LOW);  
    delay(blinkTime);
    digitalWrite(LED_BUILTIN, HIGH);  
    blinkTime = blinkTime - 25;
  }
  val = HIGH;
  digitalWrite(LED_BUILTIN, HIGH); 
}
