#include "server_thread.h"

void *ServerThread::functionThread(void *arg)
{
	ServerThread * myThread = (ServerThread *) arg;

	myThread->processor->process(myThread->serverProcessingAcceptedConnection);

	return NULL;
}

void *ServerThread::functionThread2(void *arg)
{
	IOTServer * iotSrv = (IOTServer *) arg;

	while(!iotSrv->sendMessagesToClientFromQueue())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	return NULL;
}

void ServerThread::createServerThread()
{
	pthread_create(&this->threadID1, NULL, &this->functionThread, this);
	pthread_create(&this->threadID2, NULL, &this->functionThread2, &this->serverProcessingAcceptedConnection);
}

ServerThread::ServerThread(ProcessClient *_processor_, IOTServer& _servserverProcessingAcceptedConnection_)
{
	processor = _processor_;
	serverProcessingAcceptedConnection = _servserverProcessingAcceptedConnection_;
}
