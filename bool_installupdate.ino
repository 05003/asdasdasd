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