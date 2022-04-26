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
	std::string subRegCmd("SUBREG");

	// Sends to IOT Server
	if(iotClientApp.sendRequestToServer(subRegCmd) < 0) return -1;
		
	// Checks for response
	if(iotClientApp.receiveResponseFromServer() < 0) return -1;

	// ===========================================================
	// STEP 2: Request the publisher topic listening to the IOT Server
	std::string subListenCmd;
	
	subListenCmd.append("SUBLISTENTOP,"); // Control Packet
	subListenCmd.append("sensor/temperature"); // topic ID

	// Sends to IOT Server
	if(iotClientApp.sendRequestToServer(subListenCmd) < 0) return -1;

	// Checks for response
	if(iotClientApp.receiveResponseFromServer() < 0) return -1;

	// ===========================================================
	// STEP 3: Receives payload messages from the IOT Server.
	while(keepRunning)
	{
		std::cout << "===========================================" << std::endl;

		// Checks for response
		if(iotClientApp.receiveResponseFromServer() < 0) return -1;

		// waits 0.1 second after next message receiving
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	// Closes TCP connection
    if(iotClientApp.closeConnection() < 0) return -1;

	return 0;
}
