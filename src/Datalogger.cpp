  #include "Datalogger.h"

Datalogger::Datalogger(configu *aConf){
  _configDataLogger = aConf->dataLogger;
}

int Datalogger::setFileNameToday(DS1307 *pRtc){
  String newDate = pRtc->getDateStr();
  if(_todayDate.length() != 0){
    _todayDate = newDate;
  }
  if (!_todayDate.equals(newDate)) {
    _todayDate = newDate;
    _fileNameToday = getFileNameToday(newDate);
  }
  return 0;
}

String Datalogger::getFileNameToday(String date){
  String fileName = "";

  if(_configDataLogger.prefixFile.length()!=0 && _configDataLogger.fileExtension.length()!=0){
    fileName = _configDataLogger.prefixFile + date + "."+ _configDataLogger.fileExtension;
  }
  else{
    fileName = "measurementLog"+ date +"."+_configDataLogger.fileExtension;
  }
  return fileName;
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
