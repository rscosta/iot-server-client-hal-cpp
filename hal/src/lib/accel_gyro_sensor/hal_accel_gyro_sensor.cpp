/**
 * @file hal_accel_gyro_sensor.cpp
 * @brief   HAL for Accelerometer & Gyroscope Sensor Context Interface Class
 * @author  Ricardo Costa <rcosta.am@gmail.com>
 * @date    04/01/2022
 */
#include "hal_accel_gyro_sensor.h"
#include <iostream>

using namespace std;

/**
 * Creates class object instance.
 *
 * @param none.
 * @return class handle.
 */
extern "C" AccelGyroSensor* createObject()
{
  return new AccelGyroSensor;
}

/**
 * Destroys class object instantiated.
 *
 * @param [IN]object - class handle.
 * @return none.
 */
extern "C" void destroyObject(AccelGyroSensor* object)
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
AccelGyroSensor::AccelGyroSensor()
{
  _isInitialized = false;  
}

/**
 * Starts the Accelerometer&Gyroscope Sensor hardware setup.
 *
 * @param none.
 * @return result (false = error | true = success).
 */
bool AccelGyroSensor::start()
{
  bool result = false;

  if(!_isInitialized)
  {
    _isInitialized = true;
    result = true;
    cout << "Accelerometer&Gyroscope Sensor initialized successfully!" << endl;
  }
  else
  {
    cerr << "Accelerometer&Gyroscope Sensor initialized already!" << endl;
  }

  return result;
}

/**
 * Stops/Closes the Accelerometer&Gyroscope sensor hardware.
 *
 * @param none.
 * @return result (false = error | true = success).
 */
bool AccelGyroSensor::stop()
{
  bool result = false;

  if(_isInitialized)
  {
    _isInitialized = false;
    result = true;
    cout << "Accelerometer&Gyroscope Sensor device closed successfully!" << endl;
  }
  else
  {
    cerr << "Error while closing Accelerometer&Gyroscope Sensor device!" << endl;
  }

  return result;
}

/**
 * Returns if the Accelerometer&Gyroscope Sensor device is initialized.
 *
 * @param none.
 * @return bool (true = running | false = error/not started).
 */
bool AccelGyroSensor::isInitialized()
{
  return _isInitialized;
}

/**
 * Gets the Accelerometer values (X,Y,Z) in degrees.
 * 
 * @param [OUT]AcX - X coordinate value.
 * @param [OUT]AcY - Y coordinate value.
 * @param [OUT]AcZ - Z coordinate value.
 * @return device status (true = success | false = fail/error).
 */
bool AccelGyroSensor::getAccelData(double *AcX, 
                  double *AcY,
                  double *AcZ)
{
  bool result = false;

  if(_isInitialized)
  {
    // Stub values
    *AcX = 41.12;
    *AcY = 4.34;
    *AcZ = 31.93;
    result = true;
  }
  else
  {
    *AcX = 0;
    *AcY = 0;
    *AcZ = 0;
  }

  return result;
}

/**
 * Gets the Gyroscope values (X,Y,Z) in degrees.
 * 
 * @param [OUT]GyX - X coordinate value.
 * @param [OUT]GyY - Y coordinate value.
 * @param [OUT]GyZ - Z coordinate value.
 * @return device status (true = success | false = fail/error).
 */
bool AccelGyroSensor::getGyroscopeData(double *GyX, 
                  double *GyY,
                  double *GyZ)
{
  bool result = false;

  if(_isInitialized)
  {
    // Stub values
    *GyX = 1.12;
    *GyY = 45.54;
    *GyZ = 127.93;
    result = true;
  }
  else
  {
    *GyX = 0;
    *GyY = 0;
    *GyZ = 0;
  }

  return result;
}
