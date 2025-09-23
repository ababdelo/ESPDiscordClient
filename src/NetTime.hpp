#ifndef NETTIME_HPP
#define NETTIME_HPP

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Arduino.h>

class NetTime
{
public:
  NetTime();
  void begin(int timezone = 0);
  String getTime();

private:
  WiFiUDP ntpUDP;
  NTPClient timeClient;

  const char *weekDays[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  const char *months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
                            "Aug", "Sept", "Oct", "Nov", "Dec"};
};

#endif
