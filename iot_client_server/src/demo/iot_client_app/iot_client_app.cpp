#include <termios.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <unistd.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "custom_json.h"
#include "iot_client.h"
#include "hal_temp_sensor.h"

#define HAL_TEMP_SENSOR_LIBRARY_FILE "libHALTempSensor.so"

/*
 * Detects any key pressed
 * Reference code: https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html  
 * @param none.
 * @return none.	
*/
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

int main(int argc, char *argv[])
{
	std::string serverIP = "127.0.0.1";
	unsigned short serverPort = 8080;

	try 
	{
  		// Gets server IP and port (optional) 
		if (argc == 2)
  		{
    		serverIP = argv[1];
			serverPort = (unsigned short) strtoul(argv[2], NULL, 0);    			
    	}
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}

	// Open TCP Connection
	IOTClient iotClientApp (&serverIP[0], serverPort);

	// Opens library
	void* handle = dlopen(HAL_TEMP_SENSOR_LIBRARY_FILE, RTLD_LAZY);

	// Gets HAL API object 
	TempSensor* (*create)();
	void (*destroy)(TempSensor*);

	create = (TempSensor* (*)())dlsym(handle, "createObject");
	destroy = (void (*)(TempSensor*))dlsym(handle, "destroyObject");
	TempSensor* tempSensor = (TempSensor*)create();

	// Starts driver
	bool drvRes = tempSensor->start();

	std::cout << "Driver status: " << drvRes << std::endl; 

	if(!drvRes) return -1;

	while(!kbhit())
	{
		std::cout << "===========================================" << std::endl;

		std::cout << "Press any key to finish the client application..." << std::endl;

		// Gets value from HAL
		double tempValue = 0;

		tempSensor->getTemperature(&tempValue);

		// Serialize in JSON format	
	   	json::jobject jTempSensor;

		jTempSensor["topic"] = "sensor/temperature01";
		jTempSensor["requestType"] = "PUBLISH";
		jTempSensor["deviceType"] = "temperature";
		jTempSensor["value"] = (int)tempValue;  
		std::cout << jTempSensor.pretty() << std::endl;
		
		// Prints JSON stream
		std::string tempSensorRes(jTempSensor.pretty());

		// Sends to TCP Server
		if(iotClientApp.sendRequestToServer(tempSensorRes) < 0) return -1;
		
		// Checks for response
		if(iotClientApp.receiveResponseFromServer() < 0) return -1;

		// waits 1 second
		usleep(1000000);

		std::cout << "===========================================" << std::endl;
	}

	// Stops/Closes driver
	tempSensor->stop();

	// Destroys class
	destroy( tempSensor );

	std::cout << " Driver Closed" << std::endl;

	// Closes TCP connection
    if(iotClientApp.closeConnection() < 0) return -1;

	return 0;
}
