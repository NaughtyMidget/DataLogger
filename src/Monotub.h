#ifndef Monotub_h
#define Monotub_h
//#include <OneWire.h>
#include <DallasTemperature.h>

#include "dataType.h"
#include <Arduino.h>
#include "SHT21.h"
#include "PID_v1.h"

class Monotub
{
  public:
    void loadConfig(configu aConf);
    float getSoilTemp(DallasTemperature* pSoilSensor);
    float getAirTemp(SHT21* pAirSensor);
    float getAirHumidity(SHT21* pAirSensor);
    void humidifierRun(humidifierVar* pRh, measurement* pMes);
    void humidifierStop(configu* pConf);
    void HeaterRun(PID* aPID, measurement* pMeas);
    void HeaterStop();

    int runAll(SHT21* pAirSensor, DallasTemperature* pSoilSensor);
    void stop();
  private:
    configu _configGeneral;
};

#endif
