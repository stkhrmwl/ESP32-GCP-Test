/*

updated at 2020/05/12

*/

#include <Arduino.h>
#include <MyBME280.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

bool MyBME280::isEnabled() {
  unsigned status;
  status = bme.begin(0x76);
  return status;
}

String MyBME280::getAddress() {
  byte error, address = 0x76; // 0x76
	String str = "";
	Wire.beginTransmission(address);
	error = Wire.endTransmission();
	if(error == 0) {
		str += "0x";
		if(address < 16) str += "0";
		str += String(address, HEX);
	} else if(error == 4) {
	str += "Unknown error at address 0x";
		if(address < 16) str += "0";
	str += String(address, HEX);
	} else {
		str += "No I2C devices found";
	}
	return str;
}

float MyBME280::getTemperature() {
  return bme.readTemperature();
}

float MyBME280::getPressure() {
  return bme.readPressure() / 100.0F;
}

float MyBME280::getAltitude(float seaLevel) {
  return bme.readAltitude(seaLevel);
}

float MyBME280::getHumidity() {
  return bme.readHumidity();
}