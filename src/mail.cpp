#include "mail.h"

SMTPSession smtp;
ESP_Mail_Session session;

void initEmail() {
  // 配置SMTP服务器信息
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = SMTP_USER;
  session.login.password = SMTP_PASSWORD;
}

bool sendEmail(const String& subject, const String& body, const String& attachmentPath = "") {
  SMTP_Message message;
  SMTP_Attachment att;
  
  // 配置邮件信息
  message.sender.name = SENDER_NAME;
  message.sender.email = SENDER_EMAIL;
  message.addRecipient(RECIPIENT_NAME, RECIPIENT_EMAIL);
  message.text.charSet = "UTF-8";

  // 设置邮件主题和内容
  message.subject = subject;
  message.text.content = body;
  message.clearAttachments(); // 清除之前的附件配置

  if (attachmentPath.length() > 0) {  // 如果提供了附件路径，则添加附件
    // 配置附件信息
    att.descr.filename = attachmentPath.substring(1); // 从路径中提取文件名
    att.descr.mime = "text/plain"; // 设置附件的MIME类型
    att.file.path = attachmentPath; // 设置附件的文件路径
    att.file.storage_type = esp_mail_file_storage_type_flash; // 设置附件存储类型为Flash
    message.addAttachment(att);
  }

  // 连接到SMTP服务器
  if(!smtp.connect(&session)) {
    Serial.println("Failed to connect to SMTP server");
    return 0;
  }

  // 发送邮件
  if(!MailClient.sendMail(&smtp, &message)) {
    Serial.println("Failed to send email:" + smtp.errorReason());
    return 0;
  } else {
    Serial.println("Email sent successfully");
    return 1;
  }
}