#ifndef JSON_H
#define JSON_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

#define MAX_RECIPIENTS 10   // 最大收件人数

extern String WIFI_SSID;
extern String WIFI_PASSWORD;
extern String SMTP_HOST;
extern int SMTP_PORT;
extern String SMTP_USER;
extern String SMTP_PASSWORD;
extern String SENDER_NAME;
extern String SENDER_EMAIL;
extern String RECIPIENT_NAME[MAX_RECIPIENTS];
extern String RECIPIENT_EMAIL[MAX_RECIPIENTS];
extern int recipient_count;

bool initConfig();

#endif