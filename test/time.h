#ifndef TIME_H
#define TIME_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const int timezoneOffset = 8 * 3600; // 定义时区偏移，单位为秒（这里是东八区）
const int dataRecordInterval = 29 * 1000; // 数据记录最小间隔，单位为毫秒

void initTime();
String getTime();
String getDate();

#endif