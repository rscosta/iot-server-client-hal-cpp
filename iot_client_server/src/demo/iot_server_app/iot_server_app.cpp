
#include "iot_server.h"
#include "server_thread.h"
#include "process_client.h"
#include <iostream>
#include <cstring> 
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "utils.h"
#include <algorithm>
#include <iterator>
#include <thread>

using namespace std;

void processQueueThread(IOTServer& svrHandle)
{
	std::cout << __FUNCTION__ << "initialized!" << std::endl;

	while(1)
	{
    	svrHandle.processQueue();

		// waits 1 second
		usleep(100000);
	}
}

int main(int argc, char const *argv[])
{

	int returnValue;
	std::string localIP = "127.0.0.1";
	unsigned short localPort = 8080;
	unsigned short maxConnection = 100;

	try 
	{
  		if (argc == 3)
  		{
    		localIP = argv[1];
			localPort = (unsigned short) strtoul(argv[2], NULL, 0);    			
			maxConnection = (unsigned short) strtoul(argv[3], NULL, 0);    			
		}
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << "\n";
		return 1;
	}
	// End of command parser

	IOTServer myServer(localPort, maxConnection);
	
	if(myServer.showServerIP() < 0) return -1;
	if(myServer.createServerForBindAndListen() < 0) return -1;
	if(myServer.bindServerToPortNumber() < 0) return -1;
	if(myServer.showServerPort() < 0) return -1;
	if(myServer.listenToNewClientConnection()< 0) return -1;

	std::thread thread1{ processQueueThread, std::ref(myServer) };

	while (true)
	{
        if(myServer.acceptToMakeConnectionWithClient() < 0) return -1;

	    ServerThread *myThread = new ServerThread(new ProcessClient(), myServer);
        myThread -> createServerThread();
        std::cout << "Running server" << std::endl; 
	}

	thread1.join();

	return 0;
}
