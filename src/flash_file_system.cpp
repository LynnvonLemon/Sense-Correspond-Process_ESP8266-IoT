#include "flash_file_system.h"

bool initFileSystem() { // 初始化SPIFFS文件系统
    SPIFFS.format();
    if (!SPIFFS.begin()) {
        Serial.println("Failed to Start SPIFFS");
        return 0;
    }
    Serial.println("SPIFFS Started Successfully");
    return 1;
}

void directoryInfo() {  // 列出SPIFFS根目录下的所有文件及其大小
    Dir dir = SPIFFS.openDir("/");
    Serial.println("Directory Info:");
    while (dir.next()) {
        Serial.printf("File: %s, Size: %d bytes\n", dir.fileName().c_str(), dir.fileSize());
    }
}

void writeToFile(const String& file_name, const String& data) { // 将数据追加写入指定文件
    File file = SPIFFS.open(file_name, "a");
    file.println(data);
    file.close();
}

bool removeFile(const String& file_name) {  // 删除指定文件
    return SPIFFS.remove(file_name);
}

String readFromFile(const String& file_name) {  // 从指定文件中读取内容并返回为字符串
    File file = SPIFFS.open(file_name, "r");
    String content;
    while (file.available()) {
        content += file.readStringUntil('\n');
        content += '\n';
    }
    file.close();
    return content;
}
