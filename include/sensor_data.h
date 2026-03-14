#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <Arduino.h>

#define SENSOR_PIN 32 // 定义传感器引脚
#define timeForSensorStable 1 * 1000 // 等待传感器稳定的时间，单位为毫秒

void initSensor();
int f(int& value);
int getData();

#endif