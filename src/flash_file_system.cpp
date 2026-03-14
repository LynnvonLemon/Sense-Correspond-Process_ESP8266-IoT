#include "flash_file_system.h"

bool initFileSystem() { // 初始化LittleFS文件系统
    // LittleFS.format();
    if (!LittleFS.begin()) {
        Serial.println("Failed to Start LittleFS");
        return false;
    }
    Serial.println("LittleFS Started Successfully");
    return true;
}

void directoryList(String path) {  // 列出LittleFS根目录下的所有文件及其大小
    Dir dir = LittleFS.openDir(path);
    Serial.println("Directory Info:");
    while (dir.next()) {
        Serial.printf("File: %s, Size: %d bytes\n", dir.fileName().c_str(), dir.fileSize());
    }
}

int storageInfo(){
    FSInfo fs_info;
    if(!LittleFS.info(fs_info)){
        return -1;
    }
    size_t totalBytes = fs_info.totalBytes;
    size_t usedBytes = fs_info.usedBytes;
    size_t freeSpace = totalBytes - usedBytes;
    Serial.print(String(usedBytes) + " Bytes Used / " + String(totalBytes) + "Bytes Total");
    return freeSpace;
}


void writeToFile(const String& file_name, const String& data) { // 将数据追加写入指定文件
    File file = LittleFS.open(file_name, "a");
    file.println(data);
    file.close();
}

bool removeFile(const String& file_name) {  // 删除指定文件
    return LittleFS.remove(file_name);
}

String readFromFile(const String& file_name) {  // 从指定文件中读取内容并返回为字符串
    File file = LittleFS.open(file_name, "r");
    String content;
    while (file.available()) {
        content += file.readStringUntil('\n');
        content += '\n';
    }
    file.close();
    return content;
}
