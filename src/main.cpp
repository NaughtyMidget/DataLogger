#include "Monotub.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "SHT21.h"
#include <PID_v1.h>
configu localConf =
{
  {9600, 0}, //int baudRate;  int debugSerial; **
  {1, 2, 3, 10000, 30000, 90.0, 5.0, 0}, //int En; int humiFan;  int humi;  long tOn;  long tOff;  float humiSetPoint;  float humiTolerance;  int humidifierMode;
  {1, 10, 0, 25.0, 9.1, 0.3, 1.8, 9.1, 0.3, 1.8}, //  int En;  int heaterPin;  double heatingValue;  double heatingSetPoint;  double consKp;  double consKi;  double consKd;  double aggKp;  double aggKi;  double aggKd;
  {1, 50}, //int enable;  int tempo;
  {1, 50, 6},//int enable;  int tempo;  int oneWirePort;
  //{{192, 168, 1, 13}, 80, {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF}}
};
measurement sensorData = {0.0, 0.0, 0.0};
humidifierVar humidifierData = {LOW, LOW, 0, 0, 0};

OneWire oneWire(localConf.soilSensor.oneWirePort);
DallasTemperature soilSensor(&oneWire);

SHT21 airSensor;

PID myPID(&sensorData.soilTemp, &localConf.heater.heatingValue, &localConf.heater.heatingSetPoint, localConf.heater.consKp, localConf.heater.consKi, localConf.heater.consKd, DIRECT);
Monotub myMonoTub;

void setup()
{
  myMonoTub.loadConfig(localConf);
  Serial.begin(localConf.serial.baudRate);
  Wire.begin();
  soilSensor.begin();
  pinMode(localConf.humidifier.humi, OUTPUT);
  pinMode(localConf.humidifier.humiFan, OUTPUT);
  myPID.SetMode(AUTOMATIC);

}

void loop()
{
  sensorData.airTemp = myMonoTub.getAirTemp(&airSensor);
  sensorData.airHumidity = myMonoTub.getAirHumidity(&airSensor);
  sensorData.soilTemp = myMonoTub.getSoilTemp(&soilSensor);
  Serial.println(sensorData.airTemp);
  Serial.println(sensorData.airHumidity);
  Serial.println(sensorData.soilTemp);
  Serial.println("==================");

  if (sensorData.airHumidity >= 0) {
    myMonoTub.HumidifierRun(&humidifierData, &sensorData);
  }
  else{
    myMonoTub.stop();
  }
  if(sensorData.soilTemp >= 0){
    myMonoTub.HeaterRun(&myPID, &sensorData);
  }
  else{
    myMonoTub.stop();
  }

}
