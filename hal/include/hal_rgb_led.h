// @file hal_rgb_led.h
// @brief   HAL for RGB Led Context Interface Class
// @author  Ricardo Costa <rcosta.am@gmail.com>
// @date    04/01/2022

#ifndef __HAL_RGB_LED_H__
#define __HAL_RGB_LED_H__

class RGBLed
{
public:
  RGBLed();

  // virtual is set to avoid static linkage
  virtual bool start();
  virtual bool stop();
  virtual bool isInitialized();
  virtual bool setColor(int red, int green, int blue);
  virtual bool getColor(int *red, int *green, int *blue);
  virtual bool setBrightness(int brightness);
  virtual bool getBrightness(int *brightness);

private:
  bool _isInitialized {false};
  int _red {0};
  int _green {0};
  int _blue {0};
  int _brightness {0};

};

#endif
