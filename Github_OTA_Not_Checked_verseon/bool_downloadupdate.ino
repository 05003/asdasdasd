bool downloadUpdate() {
  HTTPClient httpClient;
  httpClient.begin(otaFileName);
  int httpCode = httpClient.GET();
  Serial.println(httpCode);
  if (httpCode == HTTP_CODE_OK) {
    String url = String(otaFileName).substring(String(otaFileName).lastIndexOf('/') + 1);
    Serial.println(url);
    WiFiClient *stream = httpClient.getStreamPtr();
    Update.begin(UPDATE_SIZE_UNKNOWN);
    size_t written = Update.writeStream(*stream);
    if (written == httpClient.getSize() || httpClient.getSize() == -1) {
      Serial.println("Update downloaded");
      if (Update.end()) {
        Serial.println("Update complete");
        return true;
      } else {
        Serial.println("Update failed");
      }
    } else {
      Serial.println("Update write failed");
    }
  } else {
    Serial.println("HTTP GET failed");
  }
  return false;
}
