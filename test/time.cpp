#include "time.h"

WiFiUDP ntpUDP; // 创建WiFiUDP对象，用于NTP客户端通信
NTPClient timeClient(ntpUDP, "ntp1.aliyun.com", timezoneOffset, dataRecordInterval); // 创建NTP客户端对象，指定UDP对象、NTP服务器地址、时区偏移和更新时间间隔

void initTime() {
  timeClient.begin();
}

String getTime() {
  timeClient.update();
  String time = timeClient.getFormattedTime();
  time = time.substring(0, 5);
  return time;
}

String getDate() {
  timeClient.update();
  return String(timeClient.getDay());
}