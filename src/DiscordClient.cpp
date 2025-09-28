#include "DiscordClient.hpp"

DiscordClient::DiscordClient(const char *ssid, const char *password, const char *webhookUrl, int timezone)
    : ssid(ssid), password(password), webhookUrl(webhookUrl), _timezone(timezone), _timeInitialized(false)
{

  // Display platform information when Discord client is initialized
#if defined(ESP8266)
  Serial.println("\nESP Discord Client - Running on ESP8266");
#elif defined(ESP32)
  Serial.println("\nESP Discord Client - Running on ESP32");
#endif
}

void DiscordClient::connectWiFi()
{
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to WiFi ");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

bool DiscordClient::sendMessage(const String &content, bool includeTimestamp)
{
  // Validate webhook URL
  if (webhookUrl == nullptr || strlen(webhookUrl) == 0)
  {
    Serial.println("⚠️ Error: Webhook URL is empty");
    return false;
  }

  if (strncmp(webhookUrl, "https://discord.com/api/webhooks/", 33) != 0)
  {
    Serial.println("⚠️ Error: Invalid webhook URL format");
    return false;
  }

  WiFiClientSecure client;
  HTTPClient http;

  String message = content;

  // Only initialize time and append timestamp if requested
  if (includeTimestamp)
  {
    // Initialize time client only once
    if (!_timeInitialized)
    {
      netTime.begin(_timezone);
      _timeInitialized = true;
    }

    String currentTime = netTime.getTime();
    message = content + " " + currentTime;
  }

  client.setInsecure(); // Ignore invalid SSL certs

  // Add timeout settings
  client.setTimeout(15000); // 15 seconds timeout

  if (http.begin(client, webhookUrl))
  {
    Serial.println(" Connection to Discord established successfully.");

    // Set timeouts for HTTP client
    http.setTimeout(15000); // 15 seconds timeout
    http.addHeader("Content-Type", "application/json");
    http.addHeader("User-Agent", "ESP-Discord-Client/1.1");

    http.addHeader("Content-Type", "application/json");
    String json = "{\"content\":\"" + message + "\"}";

    // Debug output
    Serial.print("JSON payload: ");
    Serial.println(json);
    Serial.print("Sending POST request...");

    int httpCode = http.POST(json);

    Serial.print(" Response code: ");
    Serial.println(httpCode);

    http.end();

    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_NO_CONTENT)
    {
      Serial.println("✅ Message sent Successfully");
      return true;
    }
    else
    {
      Serial.printf("⚠️ Failed to send the message, response code: (%d)", httpCode);
      // Provide more detailed error information
      switch (httpCode)
      {
      case 400:
        Serial.println(" - Bad Request (check message format)");
        break;
      case 401:
        Serial.println(" - Unauthorized (invalid webhook URL)");
        break;
      case 403:
        Serial.println(" - Forbidden (webhook permissions)");
        break;
      case 404:
        Serial.println(" - Not Found (webhook doesn't exist)");
        break;
      case 429:
        Serial.println(" - Rate Limited (too many requests)");
        break;
      case -1:
        Serial.println(" - Connection failed");
        break;
      case -2:
        Serial.println(" - Send header failed");
        break;
      case -3:
        Serial.println(" - Send payload failed");
        break;
      case -4:
        Serial.println(" - Not connected");
        break;
      case -5:
        Serial.println(" - Connection lost");
        break;
      case -6:
        Serial.println(" - No stream");
        break;
      case -7:
        Serial.println(" - No HTTP server");
        break;
      case -8:
        Serial.println(" - Too less RAM");
        break;
      case -9:
        Serial.println(" - Encoding error");
        break;
      case -10:
        Serial.println(" - Stream write error");
        break;
      case -11:
        Serial.println(" - Timeout");
        break;
      default:
        Serial.println(" - Unknown error");
        break;
      }
      return false;
    }
  }
  return false;
}
