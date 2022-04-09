/**
 * @file hal_light_sensor.cpp
 * @brief   HAL for Light Sensor Context Interface Class
 * @author  Ricardo Costa <rcosta.am@gmail.com>
 * @date    04/01/2022
 */
#include "hal_light_sensor.h"
#include <iostream>

using namespace std;

/**
 * Creates class object instance.
 *
 * @param none.
 * @return class handle.
 */
extern "C" LightSensor* createObject()
{
  return new LightSensor;
}

/**
 * Destroys class object instantiated.
 *
 * @param [IN]object - class handle.
 * @return none.
 */
extern "C" void destroyObject(LightSensor* object)
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
LightSensor::LightSensor()
{
  _isInitialized = false;  
}

/**
 * Starts the Light Sensor hardware setup.
 *
 * @param none.
 * @return result (false = error | true = success).
 */
bool LightSensor::start()
{
  bool result = false;

  if(!_isInitialized)
  {
    _isInitialized = true;
    result = true;
    cout << "Light Sensor initialized successfully!" << endl;
  }
  else
  {
    cerr << "Light Sensor initialized already!" << endl;
  }

  return result;
}

/**
 * Stops/Closes the Light Sensor hardware.
 *
 * @param none.
 * @return result (false = error | true = success).
 */
bool LightSensor::stop()
{
  bool result = false;

  if(_isInitialized)
  {
    _isInitialized = false;
    result = true;
    cout << "Light Sensor device closed successfully!" << endl;
  }
  else
  {
    cerr << "Error while closing Light Sensor device!" << endl;
  }

  return result;
}

/**
 * Returns if the Light Sensor device is initialized.
 *
 * @param none.
 * @return bool (true = running | false = error/not started).
 */
bool LightSensor::isInitialized()
{
  return _isInitialized;
}

/**
 * Gets the Light Sensor value in LUX.
 * 
 * @param [OUT]value - value in LUX.
 * @return visibleLuxValue.
 */
bool LightSensor::getVisibleLux(double *value)
{
  bool result = false;

  *value = 0;

  if(_isInitialized)
  {
    // Set stub value
    double visibleLuxValue = 280.75;

    *value = visibleLuxValue;

    result = true;
  }

  return result;
}

