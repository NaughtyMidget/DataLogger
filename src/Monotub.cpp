#include "Monotub.h"
//#include "Measurement.h"
#include "SHT21.h"


void Monotub::loadConfig(configu aConf)
{
  _configGeneral = aConf;
}

int Monotub::runAll(SHT21* pAirSensor, DallasTemperature* pSoilSensor)
{
  measurement data = {0, 0, 0};

  Serial.println("Monotub is running");

  if(_configGeneral.airSensor.enable)
  {
    data.airTemp = pAirSensor->getTemperature();
    Serial.println("temperature:");
    Serial.println(data.airTemp);
  }
  if(_configGeneral.soilSensor.enable)
  {
    pSoilSensor->requestTemperaturesByIndex(0);
    data.soilTemp = pSoilSensor->getTempCByIndex(0);
    Serial.println(data.soilTemp);
    delay(1000);
  }

  return 0;
}


void Monotub::stop()
{
  Serial.println("Monotub is stopping");
  delay(1000);
}
