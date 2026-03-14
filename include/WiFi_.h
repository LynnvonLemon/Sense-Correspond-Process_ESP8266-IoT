#ifndef WIFI__H
#define WIFI__H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "config.h"

void connectWiFi();
String getTime();

#endif