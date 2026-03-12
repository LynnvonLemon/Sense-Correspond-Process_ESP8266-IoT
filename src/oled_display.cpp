#include "oled_display.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool initDisplay() { // 初始化OLED显示屏，指定电源类型和I2C地址
  pinMode(SDA_PIN, INPUT_PULLUP); // 设置I2C数据引脚为输入模式并启用内部上拉电阻
  pinMode(SCL_PIN, INPUT_PULLUP); // 设置I2C时钟引脚为输入模式并启用内部上拉电阻
  return display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
}

void updateDisplay(int x = 0, int y = 0, int size = 1, uint16_t color = SSD1306_WHITE, const String text = "") {
  display.clearDisplay();  // 清屏
  display.setCursor(x, y); // 设置光标位置
  display.setTextSize(size); // 设置字体大小
  display.setTextColor(color);  // 设置字体颜色
  display.printf("%s\n", text.c_str()); // 显示文本
  display.display();  // 执行显示
}