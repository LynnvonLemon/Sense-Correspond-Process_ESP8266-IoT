#ifndef FLASH_FILE_SYSTEM_H
#define FLASH_FILE_SYSTEM_H

#include <Arduino.h>
#include <LittleFS.h>

bool initFileSystem();
void directoryList(String path = "/");
int storageInfo();
void writeToFile(const String& file_name, const String& data);
bool removeFile(const String& file_name);
String readFromFile(const String& file_name);

#endif