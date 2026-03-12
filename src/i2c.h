#ifndef I2C_H
#define I2C_H

#include <Arduino.h>
#include <Wire.h>

#define SDA_PIN 4  // I2C总线引脚
#define SCL_PIN 5  // I2C时钟引脚

void initI2C();
int scanI2CDevices();

#endif