/**
 * @file hal_buzzer.cpp
 * @brief   HAL for Buzzer Context Interface Class
 * @author  Ricardo Costa <rcosta.am@gmail.com>
 * @date    04/01/2022
 */
#include "hal_buzzer.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

/**
 * Creates class object instance.
 *
 * @param none.
 * @return class handle.
 */
extern "C" Buzzer* createObject()
{
  return new Buzzer;
}

/**
 * Destroys class object instantiated.
 *
 * @param [IN]object - class handle.
 * @return none.
 */
extern "C" void destroyObject(Buzzer* object)
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
Buzzer::Buzzer()
{
  _isInitialized = false;  
}

/**
 * Starts the Buzzer device setup.
 *
 * @param none.
 * @return result (false = error | true = success).
 */
bool Buzzer::start()
{
  bool result = false;

  if(!_isInitialized)
  {
    _isInitialized = true;
    result = true;
    cout << "Buzzer device initialized successfully!" << endl;
  }
  else
  {
    cerr << "Buzzer device initialized already!" << endl;
  }

  return result;
}

/**
 * Stops/Closes the Buzzer device.
 *
 * @param none.
 * @return result (false = error | true = success).
 */
bool Buzzer::stop()
{
  bool result = false;

  if(_isInitialized)
  {
    _isInitialized = false;
    result = true;
    cout << "Buzzer device closed successfully!" << endl;
  }
  else
  {
    cerr << "Error while closing Buzzer device!" << endl;
  }

  return result;
}

/**
 * Returns if the Buzzer device is initialized.
 *
 * @param none.
 * @return bool (true = running | false = error/not started).
 */
bool Buzzer::isInitialized()
{
  return _isInitialized;
}

/**
 * Returns if the Buzzer is running.
 *
 * @param none.
 * @return bool (true = running | false = not running).
 */
bool Buzzer::isRunning()
{
  return _isRunning;
}

/**
 * Sets the Buzzer beep.
 * 
 * @param [IN]beepTimeMs - enable beep during a time (milliseconds).
 * @param [IN]delayMs - delay before starting beep (milliseconds).
 * @return result (true = success | false = error).
 */
bool Buzzer::setBeep(unsigned long beepTimeMs, unsigned long delayMs)
{
  using namespace std::this_thread; // sleep_for, sleep_until
  using namespace std::chrono; // nanoseconds, system_clock, seconds

  bool result = false;

  if(_isInitialized)
  {
    //Simulate Beep processing
    _isRunning = true;

    sleep_for(milliseconds(delayMs));

    sleep_for(milliseconds(beepTimeMs));

    _isRunning = false;

    result = true;
  }

  return result;
}

