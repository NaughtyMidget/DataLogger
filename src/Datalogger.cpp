  #include "Datalogger.h"

Datalogger::Datalogger(configu *aConf, DS1307 *pRtc){
  _configDataLogger = aConf->dataLogger;
  _pRtc = pRtc;
}

// test comment by gavin
int Datalogger::setFileNameToday(){
  if (_configDataLogger.enable) {
    uint8_t sl = 1;
    uint8_t fl = 1;
    char divider = '-';
    String newDate = _pRtc->getDateStr(sl,fl,divider);
    if(_todayDate.length() != 0){
      //RTC has answered
      _todayDate = newDate;
    }
    if (!_todayDate.equals(newDate)) {
      //the day has changed
      _todayDate = newDate;
      _fileNameToday = getFileNameToday(newDate);
    }
  }
  return 0;
}

String Datalogger::getFileNameToday(String date){
  /*
 Note:
 - maximum number of charactere for the file name : 8;
 - maximum number of charatere for the extension : 3;
  */
  String fileName = "";
  if (_configDataLogger.enable) {
    if((_configDataLogger.logName.length()!=0&&_configDataLogger.logName.length()<=8) && (_configDataLogger.fileExtension.length()!=0&&_configDataLogger.fileExtension.length()<=3)){
      fileName = String(_configDataLogger.logName + "." +_configDataLogger.fileExtension);
    }
    else{
      fileName = String("DataLog." + _configDataLogger.fileExtension);
    }
  }
  return fileName;
}

int Datalogger::saveMeasureToSd(measurement mes2Save){
  int error = 0;
  if (_configDataLogger.enable) {
    //ajout timestamp
    String measurementString = mes2Save.toString();
    String timesStamp = _pRtc->getTimeStr();
    String dataString = timesStamp + "," +measurementString;

    int lString = _fileNameToday.length()+1;
    char charArray[lString];
    _fileNameToday.toCharArray(charArray,lString);
    File dataFile;


    // Test comment from gavinok

    dataFile = SD.open(charArray,FILE_WRITE);

    if (dataFile) {
        Serial.println("open file");
        dataFile.println(dataString);
        dataFile.close();
      }
    else {
        Serial.println("save measure function");
        String errorMsg = "can't open file : charArray ";
        Serial.println(errorMsg);
        error = -1;
      }
  }
  return error;
}

int Datalogger::readFile2Serial(){
  int error = 0;
  if (_configDataLogger.enable) {
    int lString = _fileNameToday.length()+1;
    char charArray[lString];
    _fileNameToday.toCharArray(charArray,lString);
    File myFile;

    myFile = SD.open(charArray);
    if (myFile) {
      Serial.println("char Array.txt");
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      myFile.close();
    }
    else {
      String errorMsg = "can't open file : " + _fileNameToday;
      Serial.println("read dataFile function");
      Serial.println(errorMsg);
      error = -1;
      }
  }
  return error;
}
