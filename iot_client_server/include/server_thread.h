#ifndef _SERVER_THREAD_H_
#define _SERVER_THREAD_H_

#include <pthread.h>
#include "process_server.h"
#include "iot_server.h"

class ServerThread
{
public:
	pthread_t threadID;
	ProcessServer *processor;
	IOTServer serverProcessingAcceptedConnection;
	void createServerThread();
	static void *functionThread(void *arg);
	ServerThread(ProcessServer * _processor_, IOTServer& _servserverProcessingAcceptedConnection_);
};

#endif /*_SERVER_THREAD_H_ */