//헤더 파일과 전역 변수

#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>
#include <SPIFFS.h>

const char* ssid = "KT_GiGA_2G_Wave2_9B24";
const char* password = "fed88cz047";
const char* otaFileName = "https://raw.githubusercontent.com/05003/asdasdasd/main/Github_OTA.ino.bin";
const String currentVersion = "1.0.0";
