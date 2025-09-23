#include "NetTime.hpp"

NetTime::NetTime()
    : timeClient(ntpUDP, "pool.ntp.org") {}

void NetTime::begin(int timezone)
{
  timeClient.begin();
  // Convert hours to seconds (1 hour = 3600 seconds)
  int timeOffsetSeconds = timezone * 3600;
  timeClient.setTimeOffset(timeOffsetSeconds);
}

String NetTime::getTime()
{
  timeClient.update();

  time_t epochTime = timeClient.getEpochTime();
  String formattedTime = timeClient.getFormattedTime();
  String weekDay = weekDays[timeClient.getDay()];

  struct tm *ptm = gmtime((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon + 1;
  String monthName = months[currentMonth - 1];
  int currentYear = ptm->tm_year + 1900;

  String dateTime = weekDay + " " + String(monthDay) + " " + monthName + " " + String(currentYear) + " " + formattedTime;
  return dateTime;
}
