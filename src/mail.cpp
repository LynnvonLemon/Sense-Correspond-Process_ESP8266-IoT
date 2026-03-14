#include "mail.h"

SMTPSession smtp;
ESP_Mail_Session session;
struct MailBox {
  String subject;
  String body;
  String attachmentPath;
}mailBox[QUEUE_SIZE];  // 邮件队列，不用 SMTP_Message存是因为，加上附件，内存开销巨大，以至编译不了
int head = 0, tail = 0, cnt = 0; // 队列头、队列尾和队列大小
SMTP_Message message;

void initEmail() {
  // 配置SMTP服务器信息
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = SMTP_USER;
  session.login.password = SMTP_PASSWORD;

  // 配置邮件信息
  message.sender.name = SENDER_NAME;
  message.sender.email = SENDER_EMAIL;
  message.text.charSet = "UTF-8";
  for (int i = 0; i < recipient_count; i++) {
    message.addRecipient(RECIPIENT_NAME[i], RECIPIENT_EMAIL[i]);
  }
}

int getQueueSize() {
  return cnt;
}

bool createEmailMessage(const String& subject, const String& body, const String& attachmentPath) {  // 创建新的邮件消息并添加到队列
  if (cnt >= QUEUE_SIZE) {  // 邮件队列已满，无法创建新邮件消息
    Serial.println(F("Email queue is full. Cannot create new email message."));
    return false;
  }

  // 设置邮件主题和内容
  mailBox[tail].subject = subject;
  mailBox[tail].body = body;
  mailBox[tail].attachmentPath = attachmentPath;

  tail = (tail + 1) % QUEUE_SIZE; // 更新队列尾指针
  cnt++; // 更新队列大小
  return true;
}

bool packEmailMessage(SMTP_Message& message, const MailBox& mail) {  // 将邮件消息从队列中打包到SMTP_Message对象中
  message.subject = mail.subject;
  message.text.content = mail.body;
  if (mail.attachmentPath.length() > 0) {  // 如果邮件消息中包含附件路径，则添加附件
    message.clearAttachments();
    if(!addAttachment(message, mail.attachmentPath)) {
      Serial.println(F("Failed to add attachment to email message."));
      return false;
    }
  }
  return true;
}

bool sendNextEmail() {  // 发送队列中的下一封邮件
  if (cnt == 0) {
    Serial.println(F("Email queue is empty. No email message to send."));
    return false;
  }

  if (!smtp.connect(&session)) {
    Serial.println(F("Failed to connect to SMTP server"));
    return false;
  }

  if (!packEmailMessage(message, mailBox[head])) {
    Serial.println(F("Failed to pack email message."));
    return false;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.println(F("Failed to send email:") + smtp.errorReason());
    return false;
  }
  Serial.println(F("Email sent successfully"));
  head = (head + 1) % QUEUE_SIZE; // 更新队列头指针
  cnt--;  // 更新队列大小
  return true;
}

bool addAttachment(SMTP_Message& message, const String& attachmentPath) {
  if (attachmentPath.length() == 0) {
    Serial.println(F("No attachment path provided"));
    return false;
  }
  if (LittleFS.exists(attachmentPath) == false) {
    Serial.println(F("Attachment file does not exist"));
    return false;
  }
  SMTP_Attachment att;
  int lastSlashIndex = attachmentPath.lastIndexOf('/');
  if (lastSlashIndex == -1 || lastSlashIndex == attachmentPath.length() - 1) {
    Serial.println(F("Invalid attachment path"));
    return false;
  }
  att.descr.filename = attachmentPath.substring(lastSlashIndex + 1); // 从路径中提取文件名
  att.file.path = attachmentPath; // 设置附件的文件路径
  att.file.storage_type = esp_mail_file_storage_type_flash; // 设置附件存储类型为Flash

  message.addAttachment(att);
  return true;
}