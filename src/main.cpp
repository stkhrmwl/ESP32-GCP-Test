/******************************************************************************
 * Copyright 2018 Google
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include <Arduino.h>
#include <MyBME280.h>
#include <esp32-mqtt.h>

MyBME280 bme;

// prototype
void log(String msg);

void setup() {
  Serial.begin(115200);
  setupCloudIoT();

  delay(5000);
  Serial.println("test start");

  while (!bme.isEnabled()) {
    Serial.println("Could not find a valid BME280 sensor, do re-checking.");
    delay(5000);
  }

  log("app setup start");
}

unsigned long lastMillis = 0;

void loop() {
  mqtt->loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!mqttClient->connected()) {
    connect();
  }

  if (millis() - lastMillis > 60000) {
    lastMillis = millis();
    log(String(bme.getTemperature()));
  }
}

void log(String msg) {
  // publish処理(送信処理)
  String json = "{";
  json += "\"pub\":";
  json += msg;
  json += "}";
  Serial.println(json);
  publishTelemetry(json);
}