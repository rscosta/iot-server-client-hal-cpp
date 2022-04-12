// @file hal_temp_sensor.h
// @brief   HAL for Temperature Sensor Context Interface Class
// @author  Ricardo Costa <rcosta.am@gmail.com>
// @date    04/01/2022

#ifndef __HAL_TEMP_SENSOR_H__
#define __HAL_TEMP_SENSOR_H__

class TempSensor
{
public:
  TempSensor();

  // virtual is set to avoid static linkage
  virtual bool start();
  virtual bool stop();
  virtual bool isRunning();
  virtual bool getTemperature(double *tempValue);

private:
  bool _isInitialized {false};
};

#endif
