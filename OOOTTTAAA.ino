#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>
#include <SPIFFS.h>       //플래시 메모리 저장 할수 있게 해주는 헤더

const char* ssid = "KT_GiGA_2G_Wave2_9B24";
const char* password = "fed88cz047";
const char* otaUrl = "https://raw.githubusercontent.com/05003/asdasdasd/main/version_num.txt";
const char* otaFileName = "https://github.com/05003/asdasdasd/blob/main/Github_OTA.ino.bin"; 
const String currentVersion = "1.0.1";
bool checkForUpdates() {
  HTTPClient httpClient;
  httpClient.begin(otaUrl);

  int httpCode = httpClient.GET();                  //HTTP GET 요청
  if (httpCode == HTTP_CODE_OK) {                   //HTTP GET 요청성공
    String version = httpClient.getString();        //서버에서 반환된 버전 정보를 문자열로 읽어들임
    Serial.println("Latest version: " + version + "now version" + currentVersion);   //최신 버전 정보와 현재 버전 정보를 시리얼 모니터에 출력
    if (version != currentVersion) {                // 버전 비교
      Serial.println("New version available.");     
      return true;  
    } else {                                        
      Serial.println("Already up to date.");        
    }
  } else {
    Serial.println("Failed to get latest version.");
  }
  return false;
}
//신규 버전 다운로드

bool downloadUpdate() {
  HTTPClient httpClient;
  httpClient.begin(otaFileName);
  int httpCode = httpClient.GET();    //GET 요청을 보내고 응답코드를 저장
  if (httpCode == HTTP_CODE_OK) {     //HTTP_CODE_OK = HTTP프로토콜 200 = 통신 성공을 의미
    String url = String(otaFileName).substring(String(otaFileName).lastIndexOf('/') + 1); //'/'부터 String으로 들어가는 명령이지만, +1로 인해 '/'뒤부터 String에 저장됨
    //파일 이름 추출해서 문자열로 저장
    Serial.println(url);
    File otaFile = SPIFFS.open(otaFileName, FILE_WRITE);    // SPIFFS 파일 시스템에서 otaFileName을 열어 쓰기 모드로 otaFile 객체 생성
    httpClient.writeToStream(&otaFile);   // HTTP 응답 본문을 otaFile에 기록
    otaFile.close();
    return true;
  }
  return false;
}
bool installUpdate() {
  
  String fileName = otaFileName;                        //
  File otaFile = SPIFFS.open(otaFileName, FILE_READ);   //
  bool result = Update.begin(UPDATE_SIZE_UNKNOWN);      //
  printf("\n 1 \n");                                    //
  if (result) {                                         //
    printf("\n 2 \n");                                  //
    result = Update.writeStream(otaFile);               //
  }
  printf("\n 3 \n");
  result = Update.end();                                //
  printf("\n 4 \n");                                    //
  otaFile.close();    
  SPIFFS.remove(otaFileName);                           //
  return result;
}
void setup() {
  Serial.begin(115200);
  Serial.println(currentVersion);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected.");
}
void loop() {
  Serial.println("Checking for updates...");
  if (checkForUpdates()) {
    Serial.println("Update found. Downloading...");
    if (downloadUpdate()) {
      Serial.println("Download successful. Installing...");
      if (installUpdate()) {
        Serial.println("Update installed. Rebooting...");
        // ESP.restart();
      } else {
        Serial.println("Update installation failed.");
        Update.printError(Serial);

      }
    } else {
      Serial.println("Download failed.");
      Update.printError(Serial);
    }
  }
  delay(10000);
}