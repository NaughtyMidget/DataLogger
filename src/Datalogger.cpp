  #include "Datalogger.h"

Datalogger::Datalogger(configu *aConf, DS1307 *pRtc){
  _configDataLogger = aConf->dataLogger;
  _pRtc = pRtc;
  _sampleSavingRate = _configDataLogger.sampleSavingRate;
  _previousTime = 0;
}

int Datalogger::setFileNameToday(){
//refresh files names everyday
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
      getFileNameToday(newDate);
    }
  }
  return 0;
}

void Datalogger::getFileNameToday(String date){
  /*
 Note:
 - maximum number of charactere for the file name : 8;
 - maximum number of charatere for the extension : 3;
  */
  String fileName = "";
  if (_configDataLogger.enable) {
    if(_configDataLogger.fileLogExtension.length() <= 3&&_configDataLogger.fileErrExtension.length()<=3){
      _logFileName = String(date + "." +_configDataLogger.fileLogExtension);
      _errFileName = String(date + "." +_configDataLogger.fileErrExtension);

    }
    else{
      _logFileName = String("DataLog."+_configDataLogger.fileLogExtension);
      _errFileName = String("ErrLog" +_configDataLogger.fileErrExtension);
    }
  }
}

int Datalogger::saveMeasureToSd(measurement mes2Save){
  int error = 0;
  if (_configDataLogger.enable) {
    uint32_t timeNow = millis();
    if (timeNow - _previousTime >= _sampleSavingRate) {
        Serial.println("writing measure onto SD card");
        Serial.println(timeNow - _previousTime);
        String measurementString = mes2Save.toString();
        String timesStamp = _pRtc->getTimeStr();
        String dataString = timesStamp + "," +measurementString;

        int lString = _logFileName.length()+1;
        char fNameArr[lString];
        _logFileName.toCharArray(fNameArr,lString);
        File dataFile;

        dataFile = SD.open(fNameArr,FILE_WRITE);

        if (dataFile) {
            dataFile.println(dataString);
            dataFile.close();
          }
        else {
            Serial.println("save measure function");
            String errorMsg = "can't open file : charArray ";
            Serial.println(errorMsg);
            error = -1;
          }
      _previousTime = timeNow;
      }
    }
  return error;
}

int Datalogger::readFile2Serial(){
  int error = 0;
  if (_configDataLogger.enable) {
    int lString = _logFileName.length()+1;
    char fNameArr[lString];
    _logFileName.toCharArray(fNameArr,lString);
    File myFile;

    myFile = SD.open(fNameArr);
    if (myFile) {
      Serial.println("char Array.txt");
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
      myFile.close();
    }
    else {
      String errorMsg = "can't open file : " +_logFileName;
      Serial.println("read dataFile function");
      Serial.println(errorMsg);
      error = -1;
      }
  }
  return error;
}
