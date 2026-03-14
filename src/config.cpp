#include "config.h"

String WIFI_SSID;
String WIFI_PASSWORD;
String SMTP_HOST;
int SMTP_PORT;
String SMTP_USER;
String SMTP_PASSWORD;
String SENDER_NAME;
String SENDER_EMAIL;
String RECIPIENT_NAME[MAX_RECIPIENTS];
String RECIPIENT_EMAIL[MAX_RECIPIENTS];
int recipient_count = 0;

bool initConfig(){
    JsonDocument doc;

    File file = LittleFS.open("/config.json", "r");
    DeserializationError error = deserializeJson(doc, file);

    if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return false;
    }

    WIFI_SSID = doc[F("wifi")][F("ssid")].as<String>();
    WIFI_PASSWORD = doc[F("wifi")][F("password")].as<String>();

    JsonObject email = doc[F("email")];

    SMTP_HOST = email[F("smtp")][F("host")].as<String>();
    SMTP_PORT = email[F("smtp")][F("port")].as<int>();

    SMTP_USER = email[F("account")][F("user")].as<String>();
    SMTP_PASSWORD = email[F("account")][F("password")].as<String>();

    SENDER_NAME = email[F("sender")][F("name")].as<String>();
    SENDER_EMAIL = email[F("sender")][F("email")].as<String>();

    recipient_count = email[F("recipients")].size();
    for(int i = 0; i < recipient_count; i++) {
        RECIPIENT_NAME[i] = email[F("recipients")][i][F("name")].as<String>();
        RECIPIENT_EMAIL[i] = email[F("recipients")][i][F("email")].as<String>();
    }
    return true;
}

