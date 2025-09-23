#ifndef DISCORDCLIENT_HPP
#define DISCORDCLIENT_HPP

#include <Arduino.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <HTTPClient.h>
#endif

#include <WiFiClientSecure.h>
#include "NetTime.hpp"

class DiscordClient
{
public:
  DiscordClient(const char *ssid, const char *password, const char *webhookUrl, int timezone = 0);
  void connectWiFi();
  bool sendMessage(const String &content);

private:
  const char *ssid;
  const char *password;
  const char *webhookUrl;
  int _timezone;
  NetTime netTime;
  bool _timeInitialized;
};

#endif
