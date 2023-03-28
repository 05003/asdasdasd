#include <WiFi.h>
#include <ArduinoOTA.h>
#include "CERT.h"

const char* ssid = "KT_GiGA_2G_Wave2_9B24";
const char* password = "fed88cz047";

const char* otaHost = "github.com";
const char* otaPath = "/05003/asdasdasd/releases/download/1.0.0/Github_OTA.ino.bin";
const int otaPort = 443;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting to WiFi...");
    Serial.println(WiFi.status());
  }
  Serial.println("Connected to WiFi");

  ArduinoOTA
    .onStart([]() {
      Serial.println("OTA update starting...");
    })
    .onEnd([]() {
      Serial.println("OTA update finished!");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("OTA update progress: %u%%\n", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("OTA update error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.setHostname("OTA_Test");
  ArduinoOTA.begin();
}

void loop() {
  ArduinoOTA.handle();
}
