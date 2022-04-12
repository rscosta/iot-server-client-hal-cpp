#include "process_client.h"

void ProcessClient::process(IOTServer _serverProcessingAcceptedConnection_)
{
	bool flag = true;

	while(flag)
	{
		if(_serverProcessingAcceptedConnection_.readIncomingMessageFromClient() >= 0)
		{
			_serverProcessingAcceptedConnection_.sendResponseToClient("sucess", 200);
			usleep(6000000);
		} 
		else 
		{
			_serverProcessingAcceptedConnection_.sendResponseToClient("fail", 400);		
			flag = false;
			
		}
	}
}