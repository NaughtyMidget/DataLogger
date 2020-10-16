#ifndef DATATYPE_H
#define DATATYPE_H
#include <Arduino.h>

struct confGeneral{
  int baudRate;
  bool debugSerial;
};
struct confHumidifier{
  bool En;
  unsigned char humiFan;
  unsigned char humi;
  long tOn;
  long tOff;
  float humiSetPoint;
  float humiTolerance;
  unsigned char humidifierMode;
};
struct confHeater{
  bool En;
  unsigned char heaterPin;
  double heatingValue;
  double heatingSetPoint;
  double heaterGap;
  double consKp;
  double consKi;
  double consKd;
  double aggKp;
  double aggKi;
  double aggKd;
};
struct confAirSensor{
  bool enable;
  unsigned int tempo;
};
struct confSoilSensor{
  bool enable;
  unsigned int tempo;
  unsigned char oneWirePort;
};
struct confDatalogger{
  bool enable;
  String logName;
  String fileExtension;
};
/*struct confEthernet{
  int ipAdress[4];
  unsigned int serverPort;
  byte macAdress[];
};*/
struct configu{
  confGeneral serial; //int baudRate;  bool debugSerial;
  confHumidifier humidifier;   //unsigned charhumiFan;  iunsigned char humi;  long tOn;  long tOff;  float humiSetPoint;  float humiTolerance;  unsigned charhumidifierMode;
  confHeater heater; //  bool En;  int heaterPin;  double heatingValue;  double heatingSetPoint;  double consKp;  double consKi;  double consKd;  double aggKp;  double aggKi;  double aggKd;
  confAirSensor airSensor;  //int ennt heaterPin; able;  unsigned int tempo;
  confSoilSensor soilSensor;   //int enable;  int tempo;  unsigned char oneWirePort;
  confDatalogger dataLogger;
  //confEthernet ethernet; //byte macAdress[];   int ipAdress[4];  int serverPort;
};

struct measurement{
  float airTemp;
  float airHumidity;
  double soilTemp;
  String toString()
  {
    String meas = String(airTemp) + "," + String(airHumidity) + "," + String(soilTemp)+"\n";
    return meas;
  }
};
struct humidifierVar{
  bool flip;
  int humidifierState;
  int humidifierFanState;
  long previousTime;
  long previousMillisDuration;
  long currentTime;
};
#endif
