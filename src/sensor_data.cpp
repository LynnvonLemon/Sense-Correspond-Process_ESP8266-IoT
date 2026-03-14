#include "sensor_data.h"

void initSensor() {
  pinMode(SENSOR_PIN, INPUT); // 设置传感器引脚为输入模式
  delay(timeForSensorStable); // 等待传感器稳定
}

int f(int& value) { // 对传感器值进行处理
  return map(value, 0, 1023, 0, 100); // 将传感器值映射到0-100范围
}

int getData() {  // 读取传感器值并进行处理
  int sensorValue = analogRead(SENSOR_PIN);
  return f(sensorValue);
}