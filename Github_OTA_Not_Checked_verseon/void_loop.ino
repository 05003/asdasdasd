void loop() {
  Serial.println("Checking for updates...");
  if (downloadUpdate()) {
    Serial.println("Download successful. Installing...");
    if (installUpdate()) {
      Serial.println("Update installed. Rebooting...");
      // ESP.restart();
    } else {
      Serial.println("Update installation failed.");
    }
  } else {
    Serial.println("Download failed.");
  }
  delay(10000);
}