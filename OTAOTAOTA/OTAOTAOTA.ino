#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>

const char* host = "esp32";
const char* ssid = "KT_GiGA_2G_Wave2_9B24";
const char* password = "fed88cz047";

WebServer server(80);