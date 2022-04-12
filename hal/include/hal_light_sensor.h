// @file hal_light_sensor.h
// @brief   HAL for Light Sensor Context Interface Class
// @author  Ricardo Costa <rcosta.am@gmail.com>
// @date    04/01/2022

#ifndef __HAL_LIGHT_SENSOR_H__
#define __HAL_LIGHT_SENSOR_H__

class LightSensor
{
public:
  LightSensor();

  // virtual is set to avoid static linkage
  virtual bool start();
  virtual bool stop();
  virtual bool isInitialized();
  virtual bool getVisibleLux(double *value);

private:
  bool _isInitialized {false};
};

#endif
