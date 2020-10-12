#include "Monotub.h"
//#include "Measurement.h"
#include "SHT21.h"


void Monotub::loadConfig(configu aConf)
{
  _configGeneral = aConf;
}

float Monotub::getSoilTemp(DallasTemperature* pSoilSensor){
  float mes = 0.0;
  pSoilSensor->requestTemperatures();
  mes = pSoilSensor->getTempCByIndex(0);
  return mes;
}
float Monotub::getAirTemp(SHT21* pAirSensor){
  float mes = 0.0;
  mes = pAirSensor->getTemperature();
  return mes;
}
float Monotub::getAirHumidity(SHT21* pAirSensor){
  float mes = 0.0;
  mes = pAirSensor->getHumidity();
  return mes;
}

int Monotub::runAll(SHT21* pAirSensor, DallasTemperature* pSoilSensor)
{
  measurement data = {0, 0, 0};

  Serial.println("Monotub is running");

  if(_configGeneral.airSensor.enable)
  {
    data.airTemp = pAirSensor->getTemperature();
    Serial.println("Air temperature:");
    Serial.println(data.airTemp);
  }
  if(_configGeneral.soilSensor.enable)
  {
    pSoilSensor->requestTemperatures();
    data.soilTemp = pSoilSensor->getTempCByIndex(0);
    Serial.println("soil temperature:");
    Serial.println(data.soilTemp);
  }

  return 0;
}



void Monotub::stop()
{
  Serial.println("Monotub is stopping");
  delay(1000);
}
