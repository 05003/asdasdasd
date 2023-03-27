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