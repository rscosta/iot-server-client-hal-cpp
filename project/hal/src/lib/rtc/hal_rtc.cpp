/**
 * @file hal_rtc.cpp
 * @brief   HAL for RTC Context Interface Class
 * @author  Ricardo Costa <rcosta.am@gmail.com>
 * @date    04/01/2022
 */
#include "hal_rtc.h"
#include <iostream>
#include <random>

using namespace std;

/**
 * Creates class object instance.
 *
 * @param none.
 * @return class handle.
 */
extern "C" RTC* createObject()
{
  return new RTC;
}

/**
 * Destroys class object instantiated.
 *
 * @param [IN]object - class handle.
 * @return none.
 */
extern "C" void destroyObject(RTC* object)
{
  try
  {
    delete object;
  }
  catch(exception& e)
  {
    cerr << __FILE__ << " - Main class deallocation failed!" << endl;
  }
}

/**
 * class constructor.
 *
 * @param none.
 * @return none.
 */
RTC::RTC()
{
  _isInitialized = false;  
}

/**
 * Starts the RTC hardware setup.
 *
 * @param none.
 * @return result (false = error | true = success).
 */
bool RTC::start()
{
  bool result = false;

  if(!_isInitialized)
  {
    _isInitialized = true;
    result = true;
    cout << "RTC initialized successfully!" << endl;
  }
  else
  {
    cerr << "RTC initialized already!" << endl;
  }

  return result;
}

/**
 * Stops/Closes the RTC hardware.
 *
 * @param none.
 * @return result (false = error | true = success).
 */
bool RTC::stop()
{
  bool result = false;

  if(_isInitialized)
  {
    _isInitialized = false;
    result = true;
    cout << "RTC device closed successfully!" << endl;
  }
  else
  {
    cerr << "Error while closing RTC device!" << endl;
  }

  return result;
}

/**
 * Returns if the Light Sensor device is initialized.
 *
 * @param none.
 * @return bool (true = running | false = error/not started).
 */
bool RTC::isInitialized()
{
  return _isInitialized;
}

/**
 * Gets the RTC seconds value.
 * 
 * @param [OUT]seconds - seconds value.
 * @return bool (true = running | false = error/not started).
 */
bool RTC::getSeconds(int *seconds)
{
  bool result = false;

  if(_isInitialized)
  {
    *seconds = _seconds;

    result = true;
  }

  return result;
}

/**
 * Gets the RTC minutes value.
 * 
 * @param [OUT]minutes - minutes value.
 * @return bool (true = running | false = error/not started).
 */
bool RTC::getMinutes(int *minutes)
{
  bool result = false;

  if(_isInitialized)
  {
    *minutes = _minutes;

    result = true;
  }

  return result;
}

/**
 * Gets the RTC hours value.
 * 
 * @param [OUT]hours - hours value.
 * @return bool (true = running | false = error/not started).
 */
bool RTC::getHours(int *hours)
{
  bool result = false;

  if(_isInitialized)
  {
    *hours = _hours;

    result = true;
  }

  return result;
}

/**
 * Gets the RTC year value.
 * 
 * @param [OUT]year - year value (YYYY).
 * @return bool (true = running | false = error/not started).
 */
bool RTC::getYear(int *year)
{
  bool result = false;

  if(_isInitialized)
  {
    *year = _year;

    result = true;
  }

  return result;
}

/**
 * Gets the RTC month value.
 * 
 * @param [OUT]month - month value (MM).
 * @return bool (true = running | false = error/not started).
 */
bool RTC::getMonth(int *month)
{
  bool result = false;

  if(_isInitialized)
  {
    *month = _month;

    result = true;
  }

  return result;
}

/**
 * Gets the RTC day value.
 * 
 * @param [OUT]day - day value (DD).
 * @return bool (true = running | false = error/not started).
 */
bool RTC::getDay(int *day)
{
  bool result = false;

  if(_isInitialized)
  {
    *day = _day;

    result = true;
  }

  return result;
}

/**
 * Sets the RTC date.
 * 
 * @param [IN]day - day value (DD).
 * @param [IN]month - month value (MM).
 * @param [IN]year - year value (YYYY).
 * @return bool (true = running | false = error/not started).
 */
bool RTC::setDate(int day, int month, int year)
{
  bool result = false;

  if(_isInitialized)
  {
    _day = day;
    _month = month;
    _year = year;
    
    result = true;
  }

  return result;
}

/**
 * Sets the RTC time.
 * 
 * @param [IN]hours - hour value (HH).
 * @param [IN]minutes - minute value (MM).
 * @param [IN]seconds - seconds value (SS).
 * @return bool (true = running | false = error/not started).
 */
bool RTC::setTime(int day, int month, int year)
{
  bool result = false;

  if(_isInitialized)
  {
    _day = day;
    _month = month;
    _year = year;
    
    result = true;
  }

  return result;
}

