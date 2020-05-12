/*

updated at 2020/05/12

*/

#ifndef MyBME280_h
#define MyBME280_h

#include <Adafruit_BME280.h>

class MyBME280 {
 public:
  bool isEnabled();
  String getAddress();
  float getTemperature();
  float getPressure();
  float getAltitude(float seaLevel);
  float getHumidity();

 private:
  Adafruit_BME280 bme;
};

#endif