/**
 * @file hal_test.cpp
 * @brief   HAL API Application Test for Camera and GPS Context Interface Classes
 * @author  Ricardo Costa <rcosta.am@gmail.com>
 * @date    04/01/2022
 */
#include <iostream>
#include <string>
#include <cstdio>
#include <dlfcn.h>
#include "hal_camera.h"
#include "hal_gps.h"

using namespace std;

#define HAL_CAMERA_LIBRARY_FILE "libHALCamera.so"
#define HAL_GPS_LIBRARY_FILE "libHALGPS.so"
#define BMP_IMAGE_FILE "img_buffer.bmp"

/**
 * Tests HAL Camera API and saves a capture image to a file.
 *
 * @param none.
 * @return none.
 */
void HAL_testCameraAPI()
{
  // Opens library
  void* handle = dlopen(HAL_CAMERA_LIBRARY_FILE, RTLD_LAZY);

  // Gets API object 
  Camera* (*create)();
  void (*destroy)(Camera*);

  cout << "###############HAL CAMERA API TEST###############" << endl;

  create = (Camera* (*)())dlsym(handle, "createObject");
  destroy = (void (*)(Camera*))dlsym(handle, "destroyObject");
  Camera* camera = (Camera*)create();

  bool result = false;

  // Starts driver
  camera->start();

  // Checks if driver is initialized
  result = camera->isInitialized();

  cout << "Driver status: " << result << endl; 

  // Gets camera buffer
  string imgBuffer = camera->getImage();

  // Saves captured image into a file
  FILE *file = fopen(BMP_IMAGE_FILE, "wb");
  fwrite(imgBuffer.c_str(), sizeof(unsigned char*), imgBuffer.length(), file);
  fclose(file);

  cout << "BMP File file (" << BMP_IMAGE_FILE << ") saved in disk." << endl; 

  // Stops/Closes driver
  result = camera->stop();

  // Checks if driver is stopped
  result = camera->isInitialized();

  cout << "Driver status: " << result << endl; 

  // Destroys class
  destroy( camera );
}

/**
 * Tests HAL GPS API and gets gps data.
 *
 * @param none.
 * @return none.
 */
void HAL_testGPSAPI()
{
  // Opens library
  void* handle = dlopen(HAL_GPS_LIBRARY_FILE, RTLD_LAZY);

  // Gets API object 
  GPS* (*create)();
  void (*destroy)(GPS*);

  cout << "###############HAL GPS API TEST###############" << endl;

  create = (GPS* (*)())dlsym(handle, "createObject");
  destroy = (void (*)(GPS*))dlsym(handle, "destroyObject");
  GPS* gps = (GPS*)create();

  bool result = false;

  // Starts driver
  gps->start();

  // Checks if driver is initialized
  result = gps->isInitialized();

  cout << "Driver status: " << result << endl; 

  // Gets driver data
  double latitude = 0;
  double longitude = 0;
  double altitude  = 0;
  int nsDirection  = 0;
  int weDirection  = 0;
  double speedKnots  = 0;
  unsigned long date  = 0;
  unsigned long time  = 0;
  unsigned int satellites = 0;

  gps->getData(&latitude, 
                &longitude,
                &altitude,
                &nsDirection,
                &weDirection,
                &speedKnots,
                &date,
                &time,
                &satellites);

  cout << "Latitude: " << latitude << endl;
  cout << "Longitude: " << longitude << endl;
  cout << "Altitude: " << altitude << endl;
  cout << "nsDirection (North=0, South=1): " << nsDirection << endl;
  cout << "weDirection (West=0, East=1): " << weDirection << endl;
  cout << "Speed Knots: " << speedKnots << endl;
  cout << "date (YYYYMMDD): " << date << endl;
  cout << "time (HHMMSS): " << time << endl;
  cout << "Number of Satellites: " << satellites << endl;

  // Stops/Closes driver
  result = gps->stop();

  // Checks if driver is stopped
  result = gps->isInitialized();

  cout << "Driver status: " << result << endl; 

  // Destroys class
  destroy( gps );
}

/**
 * HAL Test Application main function.
 *
 * @param none.
 * @return 0.
 */
int main()
{
  HAL_testCameraAPI();

  HAL_testGPSAPI();

  return 0;
}
