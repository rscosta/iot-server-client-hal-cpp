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

	// ===========================================================
	// STEP 1: Request registering to the IOT Server
	std::string srvStrRes;
	int srvFuncRes = 0;
	
	std::string subRegCmd("SUBREG");

	// Sends to IOT Server
	if(iotClientApp.sendRequestToServer(subRegCmd) < 0) return -1;
		
	// Checks for response
	std::tie(srvFuncRes, srvStrRes) = iotClientApp.receiveResponseFromServer();

	if(srvFuncRes != -1)
	{
		std::cout << "SUBREG Response: " << srvStrRes << std::endl; 
	}

	// ===========================================================
	// STEP 2: Request list of topics registered for this publisher to the IOT Server
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
	// STEP 3: Request the publisher topic listening to the IOT Server
	std::string subListenCmd1;
	
	subListenCmd1.append("SUBLISTENTOP,"); // Control Packet
	subListenCmd1.append("sensor/temperature"); // topic ID

	// Sends to IOT Server
	if(iotClientApp.sendRequestToServer(subListenCmd1) < 0) return -1;

	// Checks for response
	std::tie(srvFuncRes, srvStrRes) = iotClientApp.receiveResponseFromServer();

	if(srvFuncRes != -1)
	{
		std::cout << "SUBLISTENTOP Response: " << srvStrRes << std::endl; 
	}

	// ===========================================================
	// STEP 4: Request the publisher topic listening to the IOT Server
	std::string subListenCmd2;
	
	subListenCmd2.append("SUBLISTENTOP,"); // Control Packet
	subListenCmd2.append("sensor/accelgyro"); // topic ID

	// Sends to IOT Server
	if(iotClientApp.sendRequestToServer(subListenCmd2) < 0) return -1;

	// Checks for response
	std::tie(srvFuncRes, srvStrRes) = iotClientApp.receiveResponseFromServer();

	if(srvFuncRes != -1)
	{
		std::cout << "SUBLISTENTOP Response: " << srvStrRes << std::endl; 
	}

	// ===========================================================
	// STEP 5: Receives payload messages from the IOT Server.
	while(keepRunning)
	{
		std::cout << "===========================================" << std::endl;

		// Checks for server notification
		std::tie(srvFuncRes, srvStrRes) = iotClientApp.receiveResponseFromServer();

		if(srvFuncRes != -1)
		{
			std::cout << "Server Notification: " << srvStrRes << std::endl; 
		}

		// waits 0.1 second after next message receiving
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	// Closes TCP connection
    if(iotClientApp.closeConnection() < 0) return -1;

	return 0;
}
