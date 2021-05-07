#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "fauxmoESP.h"
#define SERIAL_BAUDRATE 115200

#define WIFI_SSID "********"
#define WIFI_PASS "*******"

#define app1 "bedroom light"
#define app2 "tv"

//fauxmoESP fauxmo; 

void wifiSetup() {
  
  WiFi.mode(WIFI_STA);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  wifiSetup();

  fauxmo.createServer(true); // not needed, this is the default value
  fauxmo.setPort(80); // This is required for gen3 devices

  fauxmo.enable(true);
  fauxmo.addDevice(app1);
  fauxmo.addDevice(app2);

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
  device_id, device_name, state ? "ON" : "OFF", value);
    if ( (strcmp(device_name, app1) == 0) ) {
      if (state) {
        Serial.print("a");
      } else {
        Serial.print("b");
      }
    }
    if ( (strcmp(device_name, app2) == 0) ) {
      if (state) {
                Serial.print("c");
      } else {
        Serial.print("d");
      }
    }
  });

}

void loop() {
  fauxmo.handle();

  static unsigned long last = millis();
  if (millis() - last > 5000) {
    last = millis();
  }
}

//Arduino Code:
char data;
void setup() {
  Serial.begin(115200);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}
void loop() {
   if(Serial.available() > 0)  
  {
    data = Serial.read();      
    Serial.print(data);        
    Serial.print("\n");        
    if(data == 'a')            
      digitalWrite(4, HIGH);  
    else if(data == 'b')       
      digitalWrite(4, LOW);   
    else if(data == 'c')       
      digitalWrite(5, LOW);   
    else if(data == 'd')       
      digitalWrite(5, HIGH);   
  }                            
