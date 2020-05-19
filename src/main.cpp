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
#include <ArduinoJson.h>
#include <MyBME280.h>
#include <esp32-mqtt.h>

MyBME280 bme;

DynamicJsonDocument doc(1024);
JsonObject atomosphere = doc.createNestedObject("data");

// prototype
void publish();

void setup() {
  Serial.begin(115200);
  setupCloudIoT();

  delay(10000);
  Serial.println("Test start.");

  while (!bme.isEnabled()) {
    Serial.println("Could not find a valid BME280 sensor, do re-checking.");
    delay(5000);
  }
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
    publish();
  }
}

void publish() {
  // publish処理(送信処理)
  doc["Sensor"] = "BME280";
  atomosphere["Temperature"] = bme.getTemperature();
  atomosphere["Humidity"] = bme.getHumidity();
  String output;
  serializeJson(doc, output);
  Serial.println(output);
  publishTelemetry(output);
}