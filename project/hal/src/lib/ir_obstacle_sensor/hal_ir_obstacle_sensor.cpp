/**
 * @file hal_ir_obstable_sensor.cpp
 * @brief   HAL for IR Obstacle Sensor Context Interface Class
 * @author  Ricardo Costa <rcosta.am@gmail.com>
 * @date    04/01/2022
 */
#include "hal_ir_obstacle_sensor.h"
#include <iostream>

using namespace std;

/**
 * Creates class object instance.
 *
 * @param none.
 * @return class handle.
 */
extern "C" IRObstacleSensor* createObject()
{
  return new IRObstacleSensor;
}

/**
 * Destroys class object instantiated.
 *
 * @param [IN]object - class handle.
 * @return none.
 */
extern "C" void destroyObject(IRObstacleSensor* object)
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
IRObstacleSensor::IRObstacleSensor()
{
  _isInitialized = false;  
}

/**
 * Starts the IR Obstacle Sensor hardware setup.
 *
 * @param none.
 * @return result (false = error | true = success).
 */
bool IRObstacleSensor::start()
{
  bool result = false;

  if(!_isInitialized)
  {
    _isInitialized = true;
    result = true;
    cout << "IR Obstacle Sensor initialized successfully!" << endl;
  }
  else
  {
    cerr << "IR Obstacle Sensor initialized already!" << endl;
  }

  return result;
}

/**
 * Stops/Closes the IR Obstacle Sensor hardware.
 *
 * @param none.
 * @return result (false = error | true = success).
 */
bool IRObstacleSensor::stop()
{
  bool result = false;

  if(_isInitialized)
  {
    _isInitialized = false;
    result = true;
    cout << "IR Obstacle Sensor device closed successfully!" << endl;
  }
  else
  {
    cerr << "Error while closing IR Obstacle Sensor device!" << endl;
  }

  return result;
}

/**
 * Returns if the IR Obstacle Sensor device is initialized.
 *
 * @param none.
 * @return bool (true = running | false = error/not started).
 */
bool IRObstacleSensor::isInitialized()
{
  return _isInitialized;
}

/**
 * Gets the IR Obstacle Sensor value.
 * 
 * @param [OUT]value - (true = obstable detected | false = not obstacle detected).
 * @return result (false = error | true = success).
 */
bool IRObstacleSensor::hasObstacle(bool *value)
{
  bool result = false;

  *value = false;

  if(_isInitialized)
  {
    result = true;
    
    // Set stub value
    *value = true;
  }

  return result;
}

