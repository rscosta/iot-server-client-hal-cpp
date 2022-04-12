#include "server_thread.h"


void *ServerThread::functionThread(void *arg)
{
	ServerThread * myThread = (ServerThread *) arg;

	myThread->processor->process(myThread->serverProcessingAcceptedConnection);
	return NULL;
}

void ServerThread::createServerThread()
{
	pthread_create(&this->threadID, NULL, &this->functionThread, this);
}

ServerThread::ServerThread(ProcessServer *_processor_, IOTServer& _servserverProcessingAcceptedConnection_)
{
	processor = _processor_;
	serverProcessingAcceptedConnection = _servserverProcessingAcceptedConnection_;
}
