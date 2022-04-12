// @file hal_buzzer.h
// @brief   HAL for Buzzer Context Interface Class
// @author  Ricardo Costa <rcosta.am@gmail.com>
// @date    04/01/2022

#ifndef __HAL_BUZZER_H__
#define __HAL_BUZZER_H__

class Buzzer
{
public:
  Buzzer();

  // virtual is set to avoid static linkage
  virtual bool start();
  virtual bool stop();
  virtual bool isInitialized();
  virtual bool isRunning();
  virtual bool setBeep(unsigned long beepTimeMs, unsigned long delayMs);

private:
  bool _isInitialized {false};
  bool _isRunning {false};
};

#endif
