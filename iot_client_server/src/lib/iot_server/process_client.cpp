#include "process_client.h"

void ProcessClient::process(IOTServer _serverProcessingAcceptedConnection_)
{
	bool flag = true;

	while(flag)
	{
		int processRes = -1;
		std::string srvMsg;

	    std::tie(processRes, srvMsg) = _serverProcessingAcceptedConnection_.readIncomingMessageFromClient();

		if(processRes >= 0)
		{
			_serverProcessingAcceptedConnection_.sendResponseToClient(srvMsg, 200);
		} 
		else 
		{
			_serverProcessingAcceptedConnection_.sendResponseToClient(srvMsg, 400);		
			flag = false;
		}

		if(!_serverProcessingAcceptedConnection_.isClientConnectionAlive())
		{
			flag = false;
			
			std::cout << "Socket is not available. Closing process() listening thread." << std::endl;
		}
	}
}