
#ifndef CONFIG_HPP
#define CONFIG_HPP

// WiFi Credentials - Replace with your actual values
#define SECRET_SSID "Your_WiFi_SSID"
#define SECRET_PASS "Your_WiFi_Password"
#define SECRET_WEBHOOK "https://discord.com/api/webhooks/YOUR_WEBHOOK_URL_HERE"

// ========================================
// TIMEZONE CONFIGURATION
// ========================================
// Simply enter your timezone offset in hours from UTC:
// Examples:
//  TIMEZONE_GMT     0  = London, Dublin (UTC+0)
//  TIMEZONE_GMT_1   1  = Paris, Berlin, Madrid (UTC+1)
//  TIMEZONE_GMT_2   2  = Cairo, Athens (UTC+2)
//  TIMEZONE_GMT_8   8  = Singapore, Beijing (UTC+8)
//  TIMEZONE_EST    -5  = New York, Toronto (UTC-5)
//  TIMEZONE_PST    -8  = Los Angeles, Vancouver (UTC-8)

#define TIME_ZONE 0 // Change this to your timezone offset in hours

#endif
