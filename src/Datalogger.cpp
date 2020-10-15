  #include "Datalogger.h"

Datalogger::Datalogger(configu *aConf, DS1307 *pRtc){
  _configDataLogger = aConf->dataLogger;
  _pRtc = pRtc;
}

int Datalogger::setFileNameToday(DS1307 *pRtc){
  uint8_t sl = 1;
  uint8_t fl = 1;
  char divider = '-';
  String newDate = pRtc->getDateStr(sl,fl,divider);
  
  if(_todayDate.length() != 0){
    _todayDate = newDate;
  }
  if (!_todayDate.equals(newDate)) {
    _todayDate = newDate;
    _fileNameToday = getFileNameToday(newDate);
  }
  return 0;
}

String Datalogger::getFileNameToday(){
  String fileName = "";

  if(_configDataLogger.prefixFile.length()!=0 && _configDataLogger.fileExtension.length()!=0){
    fileName = _configDataLogger.prefixFile + date + "-"+ _configDataLogger.fileExtension;
  }
  else{
    fileName = "measurementLog"+ date +"-"+_configDataLogger.fileExtension;
  }
  return fileName;
}

String Datalogger::TestGetDate(){
  String Date = _pRtc->getDateStr();
  return Date;
}
/*int Datalogger::saveMeasureToSd(measurement mes2Save){
  int error = 0;
  String dataString = mes2Save.toString();

    if (SD.exists(_fileNameToday)) {
        File dataFile = SD.open(_fileNameToday,FILE_WRITE);
        dataFile.println(dataString);
        dataFile.close();
      }

  if (SD.exists(_fileNameToday)) {
      File dataFile = SD.open(_fileNameToday,FILE_WRITE);
      dataFile.println(dataString);
      dataFile.close();
    }
  else {
      Serial.println("error opening datalog");
    }

  return error;
}*/
