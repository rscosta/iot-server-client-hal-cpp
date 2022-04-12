// @file hal_accel_gyro_sensor.h
// @brief   HAL for Accelerometer & Gyroscope Sensor Context Interface Class
// @author  Ricardo Costa <rcosta.am@gmail.com>
// @date    04/01/2022

#ifndef __HAL_ACCEL_GYRO_SENSOR_H__
#define __HAL_ACCEL_GYRO_SENSOR_H__

class AccelGyroSensor
{
public:
  AccelGyroSensor();

  // virtual is set to avoid static linkage
  virtual bool start();
  virtual bool stop();
  virtual bool isInitialized();
  virtual bool getAccelData(double *AcX, double *AcY, double *AcZ);
  virtual bool getGyroscopeData(double *GyX, double *GyY, double *GyZ);

private:
  bool _isInitialized {false};
};

#endif
