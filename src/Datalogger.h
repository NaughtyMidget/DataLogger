#include <SD.h>
#include <SPI.h>
#include "DS1307.h"
#include "datatype.h"
class Datalogger{

public:
  Datalogger(configu *aConf, DS1307 *pRtc);
  int setFileNameToday(DS1307 *pRtc);
  String getFileNameToday(String date);
  int saveMeasureToSd(measurement mes2Save);
  String TestGetDate();
private:
  String _fileNameToday;
  confDatalogger _configDataLogger;
  DS1307 **_pRtc = NULL;
  String _todayDate;
};
