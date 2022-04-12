// @file hal_ir_obstacle_sensor.h
// @brief   HAL for IR Obstacle Sensor Context Interface Class
// @author  Ricardo Costa <rcosta.am@gmail.com>
// @date    04/01/2022

#ifndef __HAL_IR_OBSTACLE_SENSOR_H__
#define __HAL_IR_OBSTACLE_SENSOR_H__

class IRObstacleSensor
{
public:
  IRObstacleSensor();

  // virtual is set to avoid static linkage
  virtual bool start();
  virtual bool stop();
  virtual bool isInitialized();
  virtual bool hasObstacle(bool *value);

private:
  bool _isInitialized {false};
};

#endif
