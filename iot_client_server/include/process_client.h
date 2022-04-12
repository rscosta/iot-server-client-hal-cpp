#ifndef _PROCESS_CLIENT_H_
#define _PROCESS_CLIENT_H_
#include "process_server.h"

class ProcessClient:public ProcessServer
{
public:
	void process(IOTServer _serverProcessingAcceptedConnection_);

};

#endif /*_PROCESS_CLIENT_H_ */

