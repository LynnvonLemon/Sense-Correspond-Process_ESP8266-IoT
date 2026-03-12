#include "i2c.h"

void initI2C() {
  Wire.begin(SDA_PIN, SCL_PIN); // 初始化I2C总线，指定数据引脚和时钟引脚
  Wire.setClock(400000); // 设置I2C时钟频率为400kHz（可选，默认为100kHz）
}

int scanI2CDevices() { // 扫描I2C设备并返回设备数量
  Serial.printf("Scanning I2C Devices\n");
  byte error, address;
  int nDevice = 0;

  for(address = 0x01; address <= 0x7f; ++address){
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if(error == 0){
      Serial.printf("0x%02X\n", address);
      ++nDevice;
    }else if(error != 2){
      Serial.printf("Error at address 0x%02X: %d\n", address, error);
    }
  }

  if(nDevice == 0){
    Serial.println("No I2C devices found");
  }
  return nDevice;
}