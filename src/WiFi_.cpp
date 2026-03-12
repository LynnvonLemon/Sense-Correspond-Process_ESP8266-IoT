#include "WiFi_.h"

void connectWiFi() {
  //连接到WiFi网络
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.printf("Connecting to WiFi: %s\n", WIFI_SSID);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  String ipStr = WiFi.localIP().toString();
  Serial.printf("\nConnected! IP address: %s\n", ipStr.c_str());

}

String getTime() {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, "http://quan.suning.com/getSysTime.do"); //创建HTTPClient对象并指定URL
  http.addHeader("User-Agent", "ESP8266"); //添加HTTP请求头，模拟浏览器行为
  int httpCode = http.GET();  //发送HTTP GET请求并获取响应代码
  String payload = http.getString();  //获取HTTP响应的内容
  http.end();  //结束HTTP连接
  Serial.printf("Time Response Code: %d\n", httpCode);
  Serial.printf("Time Payload: %s\n", payload.c_str());
  if (httpCode != HTTP_CODE_OK) {
    Serial.println("Failed to get time");
    return ""; //返回空字符串表示获取时间失败
  }
  return payload; //返回获取到的时间字符串
}

