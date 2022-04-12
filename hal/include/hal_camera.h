// @file hal_camera.h
// @brief   HAL for Camera Context Interface Class
// @author  Ricardo Costa <rcosta.am@gmail.com>
// @date    04/01/2022

#ifndef __HAL_CAMERA_H__
#define __HAL_CAMERA_H__
#include <string>

class Camera
{
public:
  Camera();

  // virtual is set to avoid static linkage
  virtual bool start();
  virtual bool stop();
  virtual bool isInitialized();
  virtual std::string getImage();

private:
  bool _isInitialized {false};
};

#endif
