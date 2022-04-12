#ifndef _PROCESS_SERVER_H_
#define _PROCESS_SERVER_H_
#include "iot_server.h"

class ProcessServer
{
public:
	virtual void process(IOTServer serverProcessingAcceptedConnection) = 0;

};

#endif /*_PROCESS_SERVER_H_ */
