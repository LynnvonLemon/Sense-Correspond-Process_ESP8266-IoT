#include <Arduino.h>
#include "WiFi_.h"
#include "mail.h"
#include "i2c.h"
#include "oled_display.h"
#include "flash_file_system.h"
#include "sensor_data.h"

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // 设置内置LED引脚为输出模式
  digitalWrite(LED_BUILTIN, LOW); // 将内置LED设置为低电平（打开状态）
  Serial.begin(115200); // 初始化串口通信并设置其波特率为115200
  Serial.println("Initializing...");
  connectWiFi();  // 连接到WiFi网络
  initEmail();  // 初始化邮件功能
  initI2C(); // 初始化I2C总线
  scanI2CDevices(); // 扫描I2C设备并打印其地址
  initDisplay();  // 初始化OLED显示屏
  initFileSystem(); // 初始化文件系统
  initSensor(); // 初始化传感器
  digitalWrite(LED_BUILTIN, HIGH); // 将内置LED设置为高电平（关闭状态）
}

void process() {
  int data = recordData();  // 记录数据并获取处理后的整数
  Serial.printf("Recorded Data: %d\n", data); // 在串口监视器上打印记录的数据
  updateDisplay(0, 0, 2, SSD1306_WHITE, String(data)); // 在OLED显示屏上更新显示数据
  String response;
  while(response == "") {
    response = getTime();
    delay(100);
  };
  String date = response.substring(18, 23); // 获取当前日期
  String time = response.substring(24, 29); // 获取当前时间
  writeToFile("/" + date + ".txt", time + " " + String(data)); // 将数据写入文件系统中的data.txt文件
  directoryInfo(); // 列出文件系统中的文件信息
  // if (time == "23:59") { // 如果时间是23:59，则发送邮件
    String subject = "Daily Sensor Data"; // 邮件主题
    String body = "Date: " + date; // 邮件正文内容
    if (sendEmail(subject, body, "/" + date + ".txt")) {  // 邮件发送成功后删除当天的数据文件
      removeFile("/" + date + ".txt"); // 删除当天的数据文件
    } else {
      Serial.println("Failed to send email, keeping data file for retry.");  
    }
  // }
}

void loop() {
  process(); // 处理数据记录、显示和邮件发送
  delay(60 * 1000); // 等待60秒后再次记录数据
}
