/**
 * Advent of code 2018
 * @author : Nicolae Telechi
 */
#include "stdafx.h"
#include "Time.h"

// number of seconds (not counting leap seconds) since 00:00, Jan 1 1970 UTC
time_t AOC::GetTime()
{
  return std::time(nullptr);
}

time_t AOC::GetTime(int year, int month, int day, int hour, int min, int sec)
{
  struct tm tm {};
  tm.tm_year = year - 1900;
  tm.tm_mon = month - 1;
  tm.tm_mday = day;

  tm.tm_hour = hour;
  tm.tm_min = min;
  tm.tm_sec = sec;

  tm.tm_isdst = -1;

  time_t time = mktime(&tm);
  assert(time != -1);

  return time;
}

string AOC::PrintTime(time_t aTime)
{
  struct tm tm {};
  if(errno_t err = localtime_s(&tm, &aTime); err)
  {
    assert(!"Failed to convert to local time!");
    return {};
  }
  
  // put_time, asctime_s
  char buff[100];
  if (!strftime(buff, sizeof buff, "%Y-%m-%d %H:%M:%S", &tm))
  {
    assert(!"Failed to print time!");
    return{};
  }

  return buff;
}
