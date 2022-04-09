// @file hal_rtc.h
// @brief   HAL for RTC Context Interface Class
// @author  Ricardo Costa <rcosta.am@gmail.com>
// @date    04/01/2022

#ifndef __HAL_RTC_H__
#define __HAL_RTC_H__

class RTC
{
public:
  RTC();

  // virtual is set to avoid static linkage
  virtual bool start();
  virtual bool stop();
  virtual bool isInitialized();
  virtual bool getSeconds(int *seconds);
  virtual bool getMinutes(int *minutes);
  virtual bool getHours(int *hours);
  virtual bool getYear(int *year);
  virtual bool getMonth(int *month);
  virtual bool getDay(int *day);
  virtual bool setDate(int day, int month, int year);
  virtual bool setTime(int day, int month, int year);

private:
  bool _isInitialized {false};
  int _hours {0};
  int _minutes {0};
  int _seconds {0};
  int _day {0};
  int _month {0};
  int _year {0};
};

#endif
