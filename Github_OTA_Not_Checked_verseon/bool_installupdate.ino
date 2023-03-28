bool installUpdate() {
  bool result = Update.begin(UPDATE_SIZE_UNKNOWN);
  HTTPClient httpClient;
  httpClient.begin(otaFileName);
  int httpCode = httpClient.GET();
  if (httpCode == HTTP_CODE_OK) {
    String url = String(otaFileName).substring(String(otaFileName).lastIndexOf('/') + 1);
    Serial.println(url);
    int contentLength = httpClient.getSize();
    Serial.println(contentLength);
    if (contentLength > 0) {
      WiFiClient *stream = httpClient.getStreamPtr();
      Update.begin(contentLength);
      size_t written = Update.writeStream(*stream);
      if (written == contentLength) {
        Serial.println("Update written");
        if (Update.end()) {
          Serial.println("Update complete");
          SPIFFS.remove(url);
          return true;
        } else {
          Serial.println("Update end failed");
        }
      } else {
        Serial.println("Update write failed");
      }
    } else {
      Serial.println("Content-Length not found");
    }
  } else {
    Serial.println("HTTP GET failed");
  }
  Serial.println("Download failed.");
  return false;
}
