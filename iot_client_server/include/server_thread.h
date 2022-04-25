#ifndef _SERVER_THREAD_H_
#define _SERVER_THREAD_H_

#include <pthread.h>
#include <thread>
#include <chrono>
#include "process_client.h"
#include "iot_server.h"

class ServerThread
{
public:
	pthread_t threadID1;
	pthread_t threadID2;
	ProcessClient *processor;
	IOTServer serverProcessingAcceptedConnection;
	void createServerThread();
	static void *functionThread(void *arg);
	static void *functionThread2(void *arg);
	ServerThread(ProcessClient * _processor_, IOTServer& _servserverProcessingAcceptedConnection_);
};

#endif /*_SERVER_THREAD_H_ */