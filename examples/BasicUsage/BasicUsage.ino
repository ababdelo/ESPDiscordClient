#include <ESPDiscordClient.h>
#include "Config.hpp" // Contains your WiFi credentials and timezone

// Create Discord client instance
DiscordClient discord(SECRET_SSID, SECRET_PASS, SECRET_WEBHOOK, TIME_ZONE);

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  delay(1000);

  // Connect to WiFi
  discord.connectWiFi();

  // Send messages with automatic timestamp
  discord.sendMessage("Hello from ESP42!");

  // Examples with different content
  // discord.sendMessage("🚀 ESP Discord Client initialized successfully");

  // Send sensor data
  // float temperature = 13.42;
  // String sensorMsg = "🌡️ Temperature: " + String(temperature) + "°C";
  // discord.sendMessage(sensorMsg);
}

void loop()
{
  // do nothing
}
