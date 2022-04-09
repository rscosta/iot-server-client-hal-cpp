/**
 * @file hal_rgb_led.cpp
 * @brief   HAL for RGB Led Context Interface Class
 * @author  Ricardo Costa <rcosta.am@gmail.com>
 * @date    04/01/2022
 */
#include "hal_rgb_led.h"
#include <iostream>

using namespace std;

/**
 * Creates class object instance.
 *
 * @param none.
 * @return class handle.
 */
extern "C" RGBLed* createObject()
{
  return new RGBLed;
}

/**
 * Destroys class object instantiated.
 *
 * @param [IN]object - class handle.
 * @return none.
 */
extern "C" void destroyObject(RGBLed* object)
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
RGBLed::RGBLed()
{
  _isInitialized = false;  
}

/**
 * Starts the RGB Led hardware setup.
 *
 * @param none.
 * @return result (false = error | true = success).
 */
bool RGBLed::start()
{
  bool result = false;

  if(!_isInitialized)
  {
    _isInitialized = true;
    result = true;
    cout << "RGB Led initialized successfully!" << endl;
  }
  else
  {
    cerr << "RGB Led initialized already!" << endl;
  }

  return result;
}

/**
 * Stops/Closes the RGB Led hardware.
 *
 * @param none.
 * @return result (false = error | true = success).
 */
bool RGBLed::stop()
{
  bool result = false;

  if(_isInitialized)
  {
    _isInitialized = false;
    result = true;
    cout << "RGB Led device closed successfully!" << endl;
  }
  else
  {
    cerr << "Error while closing RGB Led device!" << endl;
  }

  return result;
}

/**
 * Returns if the RGB Led device is initialized.
 *
 * @param none.
 * @return bool (true = running | false = error/not started).
 */
bool RGBLed::isInitialized()
{
  return _isInitialized;
}

/**
 * Sets the RGB Led colors (Red, Green and Blue).
 * 
 * @param [IN]red - red color value (0 - 255).
 * @param [IN]green - green color value (0 - 255).
 * @param [IN]blue - blue color value (0 - 255).
 * @return result (true = success | false = error).
 */
bool RGBLed::setColor(int red, int green, int blue)
{
  bool result = false;

  if(_isInitialized)
  {
    _red = red;
    _green = green;
    _blue = blue;
    result = true;
  }

  return result;
}

/**
 * Gets the RGB Led colors (Red, Green and Blue).
 * 
 * @param [OUT]red - red color value (0 - 255).
 * @param [OUT]green - green color value (0 - 255).
 * @param [OUT]blue - blue color value (0 - 255).
 * @return result (true = success | false = error).
 */
bool RGBLed::getColor(int *red, int *green, int *blue)
{
  bool result = false;

  if(_isInitialized)
  {
    *red = _red;
    *green = _green;
    *blue = _blue;
    result = true;
  }

  return result;
}

/**
 * Sets the RGB Led brightness.
 * 
 * @param [IN]brightness - brightness percentage (0 - 100).
 * @return result (true = success | false = error).
 */
bool RGBLed::setBrightness(int brightness)
{
  bool result = false;

  if(_isInitialized)
  {
    _brightness = brightness;
    result = true;
  }

  return result;
}

/**
 * Gets the RGB Led brightness.
 * 
 * @param [OUT]brightness - brightness percentage (0 - 100).
 * @return result (true = success | false = error).
 */
bool RGBLed::getBrightness(int *brightness)
{
  bool result = false;

  if(_isInitialized)
  {
    *brightness = _brightness;
    result = true;
  }

  return result;
}
