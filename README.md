# ESP8266 传感器数据邮件系统

## 以下readme是把源文件扔给deepseek属的文档

## 项目简介
这是一个基于ESP8266的传感器数据采集系统，可以定时读取传感器数据，保存到文件系统，并在每天23:59通过邮件发送当天的数据统计报告。

## 功能特点
- 📊 定时采集传感器数据
- 💾 数据保存到LittleFS文件系统
- 📧 每天自动发送邮件报告
- 📁 支持附件发送（数据文件）
- 🖥 OLED显示屏实时显示数据
- ⚙️ 通过JSON配置文件设置参数

## 工作原理
1. 启动时初始化各模块，从配置文件读取参数
2. 每分钟读取一次传感器数据
3. 数据保存到以日期命名的文件（如 /03-15.txt）
4. 每天23:59发送邮件报告，包含当天数据的平均值、最大值、最小值
5. 发送成功后删除当天数据文件

## 硬件要求
- ESP8266开发板（如ESP-12E）
- 传感器（连接GPIO32）
- OLED显示屏（SSD1306，I2C接口）
- 杜邦线若干

## 文件说明
- src/ - 源代码文件
- include/ - 头文件
- data/ - 配置文件（上传到LittleFS）

## 引脚连接
| 设备 | 引脚 |
|------|------|
| OLED SDA | GPIO4 |
| OLED SCL | GPIO5 |
| 传感器 | GPIO32 |

## 软件配置

### 1. 安装依赖库
项目使用PlatformIO，会自动安装以下库：
- ArduinoJson
- Adafruit SSD1306
- Adafruit GFX Library
- ESP Mail Client

### 2. 配置文件
复制 `data/config.example.json` 为 `data/config.json`，并按照同目录下的README.md提示填写信息：

## 📦 版本历史

### v0.0 (初始版本)
- 基础传感器数据采集
- 简单邮件发送功能
- SPIFFS文件系统
- 硬编码配置

### v1.0 (2026-03-15)

#### 🆕 新增功能
1. 配置系统
✨ 新增 config.cpp/h，支持从JSON文件读取配置

✨ 添加 config.json 配置文件，包含WiFi、邮箱、收件人等信息

✨ 支持多个收件人（最多10个）

✨ 添加 config.example.json 作为配置模板

2. 邮件队列系统
✨ 新增 MailBox 结构体存储邮件信息（subject, body, attachmentPath）

✨ 实现环形队列（head/tail/cnt），支持多邮件排队发送

✨ 队列大小 QUEUE_SIZE = 128

✨ 新增 createEmailMessage() 将邮件加入队列

✨ 新增 packEmailMessage() 打包邮件

✨ 新增 sendNextEmail() 逐个发送队列中的邮件

3. 数据统计功能
✨ 新增全局变量 data_max, data_min, data_sum, data_cnt

✨ 在邮件正文中发送平均值、最大值、最小值统计报告

4. 文件系统增强
✨ 新增 storageInfo() 获取文件系统空间信息

✨ directoryList() 支持指定路径参数

5. 项目文档
✨ 添加 README.md 项目说明

✨ 添加 LICENSE.txt MIT许可证

✨ 添加 data/README.md 配置说明

#### 🔧 改进优化
1. 文件系统
🔄 SPIFFS → LittleFS（更稳定、更快）

🔄 FS.h → LittleFS.h

🔄 移除 SPIFFS.format()（避免每次都格式化）

🔄 directoryInfo() → directoryList()

2. 邮件功能
🔄 单邮件发送 → 队列系统（解决内存问题）

🔄 硬编码配置 → 从JSON读取

🔄 修复附件重复问题（添加 message.clearAttachments()）

3. WiFi配置
🔄 硬编码宏 → 从JSON读取

🔄 WiFi.begin(WIFI_SSID, WIFI_PASSWORD) → WiFi.begin(WIFI_SSID.c_str(), WIFI_PASSWORD.c_str())

🔄 头文件包含 config.h

4. 传感器数据
🔄 recordData() → getData()（命名更规范）

🔄 添加数据统计功能

5. 初始化顺序
🔄 调整 setup() 顺序：文件系统 → 配置 → WiFi → 其他

🔄 添加配置依赖说明

#### 🐛 Bug修复
修复附件重复发送问题（clearAttachments()）

修复文件系统挂载顺序问题

修复WiFi连接字符串类型问题

#### 📦 项目结构完善
添加 config.cpp/h 配置文件管理

添加 data/ 目录存放配置文件

添加 platformio.ini 完善配置（文件系统过滤、库忽略等）

完善头文件互相包含关系

#### ⚡ 性能优化
邮件队列减少内存占用（不直接存 SMTP_Message）

LittleFS 替换 SPIFFS

移除不必要的格式化操作

#### 🔐 安全性提升
敏感信息从代码移到JSON配置文件

添加配置文件模板，不上传真实密码

完善 .gitignore 保护隐私