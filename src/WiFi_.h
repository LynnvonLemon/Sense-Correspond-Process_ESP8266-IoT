#ifndef WIFI__H
#define WIFI__H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define WIFI_SSID "要成功先发疯" //定义WiFi网络的SSID
#define WIFI_PASSWORD "li156683359" //定义WiFi网络的密码

void connectWiFi();
String getTime();

#endif