#include <SD.h>
#include <SPI.h>
#include "DS1307.h"
#include "datatype.h"
class Datalogger{

public:
  Datalogger(configu *aConf);
  int setFileNameToday(DS1307 *pRtc);
  String getFileNameToday(String date);
  int saveMeasureToSd(measurement mes2Save);
private:
  String _fileNameToday;
  confDatalogger _configDataLogger;
  String _todayDate;
};
