//헤더 파일과 전역 변수

#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>
#include <SPIFFS.h>       //플래시 메모리 저장 할수 있게 해주는 헤더

const char* ssid = "KT_GiGA_2G_Wave2_9B24";
const char* password = "fed88cz047";
const char* otaUrl = "https://raw.githubusercontent.com/05003/asdasdasd/main/version_num.txt";
const char* otaFileName = "https://github.com/05003/asdasdasd/blob/main/Github_OTA.ino.bin"; 
const String currentVersion = "1.0.1";
//주소속 OTA 파일 이름이 다르면 오류 발생
//스캐치 - 컴파일된 바이너리 내보내기 - 프로젝트명.ino.bin 파일 등록 