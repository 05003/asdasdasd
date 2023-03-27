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