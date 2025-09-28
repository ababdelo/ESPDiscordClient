#include <ESPDiscordClient.h>
#include "Config.hpp" // Contains your WiFi credentials and timezone

// Create Discord client instance
DiscordClient discord(SECRET_SSID, SECRET_PASS, SECRET_WEBHOOK, TIME_ZONE);

void setup()
{
  Serial.begin(9600);

  // Connect to WiFi
  discord.connectWiFi();

  // Send simple message without timestamp
  discord.sendMessage("Hi there! 👋", false);

  delay(1000);

  // Examples with timestamp (explicit)
  discord.sendMessage("🚀 ESP Discord Client initialized successfully"); // Default adds timestamp

  // Send sensor data with timestamp
  // float temperature = 13.42;
  // String sensorMsg = "🌡️ Temperature: " + String(temperature) + "°C";
  // discord.sendMessage(sensorMsg, true);  // with timestamp
  
  // Send alert with timestamp
  // discord.sendMessage("🚨 ALERT: SYSTEM IS OVERHEATING 🚨", true);
}

void loop()
{
  // do nothing
}
