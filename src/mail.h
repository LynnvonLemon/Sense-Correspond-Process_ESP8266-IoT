#ifndef MAIL_H
#define MAIL_H

#include <Arduino.h>
#include <ESP_Mail_Client.h>

#define SMTP_HOST "smtp.163.com"
#define SMTP_PORT 465

#define SMTP_USER ""
#define SMTP_PASSWORD ""

#define SENDER_NAME ""
#define SENDER_EMAIL ""
#define RECIPIENT_NAME ""
#define RECIPIENT_EMAIL ""

void initEmail();
bool sendEmail(const String& subject, const String& body, const String& attachmentPath);

#endif