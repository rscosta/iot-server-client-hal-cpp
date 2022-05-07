#include <signal.h>
#include <termios.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <unistd.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <sstream>
#include <tuple>
#include "iot_client.h"
#include "hal_accel_gyro_sensor.h"

#define HAL_LIBRARY_FILE "libHALAccelGyroSensor.so"

static volatile int keepRunning = 1;

void intHandler(int sig)
{
    keepRunning = 0;
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

	//Register CTRL+C signal
   	signal(SIGINT, intHandler);
 
	// Open TCP Connection
	IOTClient iotClientApp (&serverIP[0], serverPort);

	// Opens library
	void* handle = dlopen(HAL_LIBRARY_FILE, RTLD_LAZY);

	// Gets HAL API object 
	AccelGyroSensor* (*create)();
	void (*destroy)(AccelGyroSensor*);

	create = (AccelGyroSensor* (*)())dlsym(handle, "createObject");
	destroy = (void (*)(AccelGyroSensor*))dlsym(handle, "destroyObject");
	AccelGyroSensor* accelGyroSensor = (AccelGyroSensor*)create();

	// Starts driver
	bool drvRes = accelGyroSensor->start();

	std::cout << "Driver status: " << drvRes << std::endl; 

	if(!drvRes) return -1;

	// ===========================================================
	// Checks for response
	std::string srvStrRes;
	int srvFuncRes = 0;
	
	// STEP 1: Request registering to the IOT Server
	std::string pubRegCmd("PUBREG");

	// Sends to IOT Server
	if(iotClientApp.sendRequestToServer(pubRegCmd) < 0) return -1;
		
	// Checks for response
	std::tie(srvFuncRes, srvStrRes) = iotClientApp.receiveResponseFromServer();

	if(srvFuncRes != -1)
	{
		std::cout << "PUBREG Response: " << srvStrRes << std::endl; 
	}

	// ===========================================================
	// STEP 2: Request the publisher topic registering to the IOT Server
	std::string pubRegTopicCmd;
	
	pubRegTopicCmd.append("PUBREGTOP,"); // Control Packet
	pubRegTopicCmd.append("sensor/accelgyro"); // topic ID

	// Sends to IOT Server
	if(iotClientApp.sendRequestToServer(pubRegTopicCmd) < 0) return -1;

	// Checks for response
	std::tie(srvFuncRes, srvStrRes) = iotClientApp.receiveResponseFromServer();

	if(srvFuncRes != -1)
	{
		std::cout << "PUBREGTOP Response: " << srvStrRes << std::endl; 
	}

	// ===========================================================
	// STEP 3: Request list of topics registered for this publisher to the IOT Server
	std::string pubListTopicCmd("PUBLISTTOP");

	// Sends to IOT Server
	if(iotClientApp.sendRequestToServer(pubListTopicCmd) < 0) return -1;
		
	// Checks for response
	std::tie(srvFuncRes, srvStrRes) = iotClientApp.receiveResponseFromServer();

	if(srvFuncRes != -1)
	{
		std::cout << "PUBLISTTOP Response: " << srvStrRes << std::endl; 
	}

	// ===========================================================
	// STEP 4: Sends message (topic + sensor value(s)) to the IOT Server each x seconds.
	while(keepRunning)
	{
		std::cout << "===========================================" << std::endl;

		// Gets value from HAL
		double AcX = 0;
		double AcY = 0;
        double AcZ = 0;
		
		accelGyroSensor->getAccelData(&AcX, &AcY, &AcZ);

		double GyX = 0;
		double GyY = 0;
        double GyZ = 0;
		
		accelGyroSensor->getGyroscopeData(&GyX, &GyY, &GyZ);
		
		// Serialize Message to be sent to IOT Server
		std::ostringstream pubSendDataCmd;
		pubSendDataCmd << "SENDPAYLOAD,"; // Contol packet
		pubSendDataCmd << "sensor/accelgyro,"; // Topic ID

		
		// Accelerometer data
		pubSendDataCmd << AcX << " ";
		pubSendDataCmd << AcY << " ";
		pubSendDataCmd << AcZ << " ";

		// Accelerometer data
		pubSendDataCmd << GyX << " ";
		pubSendDataCmd << GyY << " ";
		pubSendDataCmd << GyZ;

		std::string accelGyroSensorRes(pubSendDataCmd.str());

		// Sends to TCP Server
		if(iotClientApp.sendRequestToServer(accelGyroSensorRes) < 0) return -1;
		
		// Checks for response
		std::tie(srvFuncRes, srvStrRes) = iotClientApp.receiveResponseFromServer();

		if(srvFuncRes != -1)
		{
			std::cout << "SENDPAYLOAD Response: " << srvStrRes << std::endl; 
		}

		// waits 1 second after next publishing
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	// Closes TCP connection
    if(iotClientApp.closeConnection() < 0) return -1;

	// Stops/Closes driver
	accelGyroSensor->stop();

	// Destroys class
	destroy( accelGyroSensor );

	std::cout << " Driver Closed" << std::endl;

	return 0;
}
