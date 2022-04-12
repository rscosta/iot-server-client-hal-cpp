/**
 * @file hal_gps.cpp
 * @brief   HAL for Global Positioning System Context Interface Class
 * @author  Ricardo Costa <rcosta.am@gmail.com>
 * @date    04/01/2022
 */
#include "hal_gps.h"
#include <iostream>
#include <random>

using namespace std;

/**
 * Creates class object instance.
 *
 * @param none.
 * @return class handle.
 */
extern "C" GPS* createObject()
{
  return new GPS;
}

/**
 * Destroys class object instantiated.
 *
 * @param [IN]object - class handle.
 * @return none.
 */
extern "C" void destroyObject(GPS* object)
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
GPS::GPS()
{
  _isInitialized = false;  
}

/**
 * Starts the GPS Module hardware setup.
 *
 * @param none.
 * @return result (false = error | true = success).
 */
bool GPS::start()
{
  bool result = false;

  if(!_isInitialized)
  {
    _isInitialized = true;
    result = true;
    cout << "GPS Module initialized successfully!" << endl;
  }
  else
  {
    cerr << "GPS Module initialized already!" << endl;
  }

  return result;
}

/**
 * Stops/Closes the GPS Module hardware.
 *
 * @param none.
 * @return result (false = error | true = success).
 */
bool GPS::stop()
{
  bool result = false;

  if(_isInitialized)
  {
    _isInitialized = false;
    result = true;
    cout << "GPS Module closed successfully!" << endl;
  }
  else
  {
    cerr << "Error while closing GPS Module!" << endl;
  }

  return result;
}

/**
 * Returns the GPS Module is initialized.
 *
 * @param none.
 * @return result (false = error/not initialized | true = initialized).
 */
bool GPS::isInitialized()
{
  return _isInitialized;
}

/**
 * Gets the GPS Module parameters.
 * 
 * @param [OUT]latitude - latitude value.
 * @param [OUT]longitude - longitude value.
 * @param [OUT]altitude - altitude value.
 * @param [OUT]nsDirection - North(0) or South(1) values.
 * @param [OUT]weDirection - West(0) or East(1) values.
 * @param [OUT]speedKnots - speed in knots.
 * @param [OUT]date - date in format yymmdd.
 * @param [OUT]time - time in format hhmmss.
 * @param [OUT]satellites - number of satellites.
 * @return gps status (true = success | false = fail/error).
 */
bool GPS::getData(double *latitude, 
                  double *longitude,
                  double *altitude,
                  int *nsDirection,
                  int *weDirection,
                  double *speedKnots,
                  unsigned long *date,
                  unsigned long *time,
                  unsigned int *satellites)
{
  bool result = false;

  if(_isInitialized)
  {
    // Stub values
    *latitude = 41.12629;
    *longitude = -8.640751333;
    *altitude = -31.937;
    *nsDirection = 0;
    *weDirection = 1;
    *speedKnots = 0.182;
    *date = 210101;
    *time = 100222;
    *satellites = 6;
    result = true;
  }
  else
  {
    *latitude = 0;
    *longitude = 0;
    *altitude = 0;
    *nsDirection = 0;
    *weDirection = 0;
    *speedKnots = 0;
    *date = 0;
    *time = 0;
    *satellites = 0;
  }

  return result;
}

