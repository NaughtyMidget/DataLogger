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

void Monotub::humidifierRun(humidifierVar* pRh, measurement* pMes)
{
    if(_configGeneral.humidifier.En == 1)
    {
      switch(_configGeneral.humidifier.humidifierMode)
      {
        case 0:
            Serial.println("regul Humidifier mode 0");
            float outputDuration[2];
            outputDuration[0] = _configGeneral.humidifier.tOn;
            outputDuration[1] = _configGeneral.humidifier.tOff;
            pRh->currentTime = millis();

            if (pRh->currentTime - pRh->previousTime >= outputDuration[pRh->flip])
            {
              pRh->flip = !pRh->flip;
              Serial.println(pRh->flip);
              pRh->previousTime = pRh->currentTime;
              digitalWrite(_configGeneral.humidifier.humi, pRh->flip);
              delay(2000);
              digitalWrite(_configGeneral.humidifier.humiFan, pRh->flip);
            }
            break;
        case 1:
            if(_configGeneral.humidifier.humiSetPoint - _configGeneral.humidifier.humiTolerance <= pMes->airHumidity && _configGeneral.humidifier.humiSetPoint + _configGeneral.humidifier.humiTolerance >= pMes->airHumidity)
            {
              pRh->humidifierState = LOW;
              pRh->humidifierFanState = LOW;
            }
            else
            {
              pRh->humidifierState = HIGH;
              pRh->humidifierFanState = HIGH;
            }
            digitalWrite(_configGeneral.humidifier.humi, pRh->humidifierState);
            delay(2000);
            digitalWrite(_configGeneral.humidifier.humiFan, pRh->humidifierFanState);
            break;
      }
    }
}
void Monotub::humidifierStop(configu* pConf)
{
  digitalWrite(_configGeneral.humidifier.humi,LOW);
  digitalWrite(_configGeneral.humidifier.humiFan,LOW);
}

void Monotub::stop()
{
  Serial.println("Monotub is stopping");
  delay(1000);
}

void Monotub::HeaterRun(PID* aPID, measurement* pMeas)
{
  if(_configGeneral.heater.En == 1)
  {
      double gap = abs(_configGeneral.heater.heatingSetPoint - pMeas->soilTemp);

      if(gap<_configGeneral.heater.heaterGap)
      {
        aPID->SetTunings(_configGeneral.heater.consKp, _configGeneral.heater.consKi, _configGeneral.heater.consKd);
      }
      else
      {
        aPID->SetTunings(_configGeneral.heater.aggKp, _configGeneral.heater.aggKi, _configGeneral.heater.aggKd);
      }
      aPID->Compute();
      analogWrite(_configGeneral.heater.heaterPin, _configGeneral.heater.heatingValue);
  }
}

void Monotub::HeaterStop()
{
  analogWrite(_configGeneral.heater.heaterPin, 0);
}
