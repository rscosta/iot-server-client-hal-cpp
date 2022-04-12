/**
 * @file hal_temp_sensor.cpp
 * @brief   HAL for Temperature Sensor Context Interface Class
 * @author  Ricardo Costa <rcosta.am@gmail.com>
 * @date    04/01/2022
 */
#include "hal_temp_sensor.h"
#include <iostream>
#include <random>

using namespace std;

/**
 * Creates class object instance.
 *
 * @param none.
 * @return class handle.
 */
extern "C" TempSensor* createObject()
{
  return new TempSensor;
}

/**
 * Destroys class object instantiated.
 *
 * @param [IN]object - class handle.
 * @return none.
 */
extern "C" void destroyObject(TempSensor* object)
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
TempSensor::TempSensor()
{
  _isInitialized = false;  
}

/**
 * Starts the Temperature sensor hardware setup.
 *
 * @param none.
 * @return result (false = error | true = success).
 */
bool TempSensor::start()
{
  bool result = false;

  if(!_isInitialized)
  {
    _isInitialized = true;
    result = true;
    cout << "Temperature Sensor initialized successfully!" << endl;
  }
  else
  {
    cerr << "Temperature Sensor initialized already!" << endl;
  }

  return result;
}

/**
 * Stops/Closes the Temperature sensor hardware.
 *
 * @param none.
 * @return result (false = error | true = success).
 */
bool TempSensor::stop()
{
  bool result = false;

  if(_isInitialized)
  {
    _isInitialized = false;
    result = true;
    cout << "Temperature Sensor device closed successfully!" << endl;
  }
  else
  {
    cerr << "Error while closing Temperature Sensor device!" << endl;
  }

  return result;
}

/**
 * Returns if the Temperature sensor is running.
 *
 * @param none.
 * @return result (false = not running | true = running).
 */
bool TempSensor::isRunning()
{
  return _isInitialized;
}

/**
 * Gets the Temperature sensor value in Celsius (°C).
 * 
 * @param [OUT]tempValue - Temperature value.
 * @return result (true = success | false = error).
 */
bool TempSensor::getTemperature(double *tempValue)
{
  double lowerBound = 12.0;
  double upperBound = 20.0;
  bool result = false;

  if(_isInitialized)
  {
    // Generate random temperature based on lowerBound to upperBound
    uniform_real_distribution<double> unifDist(lowerBound, upperBound);
    
    default_random_engine rEngine;

    *tempValue = unifDist(rEngine);

    result = true; 
  }

  return result;
}
