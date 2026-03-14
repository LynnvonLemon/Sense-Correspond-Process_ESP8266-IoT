#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "i2c.h"

#define OLED_RESET 4  // 自定义OLED重置引脚
#define OLED_ADDRESS 0x3C // 定义OLED显示屏的I2C地址
#define SCREEN_WIDTH 128 // 设置OLED宽度,单位:像素
#define SCREEN_HEIGHT 64 // 设置OLED高度,单位:像素

bool initDisplay();
void updateDisplay(int x, int y, int size, uint16_t color, const String text);

#endif