// @file hal_gps.h
// @brief   HAL for Global Positioning System Context Interface Class
// @author  Ricardo Costa <rcosta.am@gmail.com>
// @date    04/01/2022

#ifndef __HAL_GPS_H__
#define __HAL_GPS_H__

class GPS
{
public:
  GPS();

  // virtual is set to avoid static linkage
  virtual bool start();
  virtual bool stop();
  virtual bool isInitialized();
  virtual bool getData(double *latitude, 
                  double *longitude,
                  double *altitude,
                  int *nsDirection,
                  int *weDirection,
                  double *speedKnots,
                  unsigned long *date,
                  unsigned long *time,
                  unsigned int *satellites);

private:
  bool _isInitialized {false};
};

#endif
