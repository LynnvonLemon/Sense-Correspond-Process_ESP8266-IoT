#include <Arduino.h>
#include "flash_file_system.h"
#include "config.h"
#include "WiFi_.h"
#include "mail.h"
#include "i2c.h"
#include "oled_display.h"
#include "sensor_data.h"

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // 设置内置LED引脚为输出模式
  digitalWrite(LED_BUILTIN, LOW); // 将内置LED设置为低电平（打开状态）
  Serial.begin(115200); // 初始化串口通信并设置其波特率为115200
  Serial.println("Initializing...");
  initFileSystem(); // 初始化文件系统
  initConfig(); // 依赖文件系统，必须于其后初始化
  connectWiFi();  // 连接到WiFi网络
  initEmail();  // 初始化邮件功能
  initI2C(); // 初始化I2C总线
  scanI2CDevices(); // 扫描I2C设备并打印其地址
  initDisplay();  // 初始化OLED显示屏
  initSensor(); // 初始化传感器
  digitalWrite(LED_BUILTIN, HIGH); // 将内置LED设置为高电平（关闭状态）
}

int data_max = 0, data_min = 2147483647, data_sum, data_cnt;
void process() {
  int data = getData();  // 记录数据并获取处理后的整数
  data_max = max(data, data_max);
  data_min = min(data, data_min);
  data_sum += data;
  data_cnt++;

  Serial.printf("Recorded Data: %d\n", data); // 在串口监视器上打印记录的数据
  updateDisplay(0, 0, 2, SSD1306_WHITE, String(data)); // 在OLED显示屏上更新显示数据

  String response;
  while (response == "") {
    response = getTime();
    delay(100);
  };
  String date = response.substring(18, 23); // 获取当前日期
  String time = response.substring(24, 29); // 获取当前时间
  String fileName = "/" + date + ".txt";

  writeToFile(fileName, time + " " + String(data)); // 将时间和数据写入以日期命名的文件中

  if (time == "23:59") { // 如果时间是23:59，则发送邮件
    String subject = F("Daily Sensor Data"); // 邮件主题
    String body = "Date: " + date + 
                  "\nAvr: " + String(1.0 * data_sum / data_cnt) + 
                  "\nMax: " + String(data_max) + 
                  "\nMin: " + String(data_min) + 
                  "\n"; // 邮件正文内容
    if(createEmailMessage(subject, body, fileName)) { // 创建邮件消息并添加到队列
      data_max = 0;
      data_min = 2147483647;
    }
    while (getQueueSize() > 0) { // 发送邮件队列中的所有邮件
      if (!sendNextEmail()) {
        break; // 如果发送邮件失败，则停止尝试发送剩余的邮件
      }
    }
  }
}

void loop() {
  process(); // 处理数据记录、显示和邮件发送
  delay(60 * 1000); // 等待60秒后再次记录数据
}
