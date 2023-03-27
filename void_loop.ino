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