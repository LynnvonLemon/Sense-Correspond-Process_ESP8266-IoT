#ifndef MAIL_H
#define MAIL_H

#include <Arduino.h>
#include <ESP_Mail_Client.h>
#include "config.h"
#include "flash_file_system.h"

#define SMTP_HOST "smtp.163.com"
#define SMTP_PORT 465

#define QUEUE_SIZE 128

void initEmail();
int getQueueSize();
bool createEmailMessage(const String& subject, const String& body, const String& attachmentPath = "");
bool sendNextEmail();
bool addAttachment(SMTP_Message& message, const String& attachmentPath);

#endif