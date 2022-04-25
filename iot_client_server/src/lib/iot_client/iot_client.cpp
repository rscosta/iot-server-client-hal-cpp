#include "iot_client.h"

IOTClient::IOTClient(char *_serverIP_, unsigned short _serverPort_)
{
	std::cout<<"Client initializing ..." << std::endl;

	serverPortNumber() = _serverPort_;
	this->createClientForConnection();

	serverIP_ = gethostbyname(_serverIP_);

	if (serverIP_ == NULL)
	{
		std::cout<<"Error host not found"
					<<strerror(h_errno)<<"" << std::endl;
	}
	else
	{
		std::cout<<"Client initialized" << std::endl;
	}

	this->connectClientToServer();
}

int IOTClient::createClientForConnection()
{
	int returnValue = 0;

	std::cout << "Creating a client socket ..." << std::endl;

	socketConnectToClient_ = socket(AF_INET, SOCK_STREAM, 0);
	
	if (socketConnectToClient_ < 0)
	{
		returnValue = -1; 
		std::cout <<"Error while creating a client socket"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl; 
	}
	else
	{
		std::cout << "A client socket created" << std::endl;
	}

	return returnValue;
}

int IOTClient::connectClientToServer()
{
	int returnValue = 0;
	std::cout << "Connecting to a server ..." << std::endl;

	bzero((char *) &serverAddress(), sizeof(serverAddress()));

    serverAddress().sin_family = AF_INET;

    bcopy((char *)serverIP_->h_addr, (char *)&serverAddress().sin_addr.s_addr,
	serverIP_->h_length);

    serverAddress().sin_port = htons(serverPortNumber());

    if (connect(socketConnectToClient_,(struct sockaddr *) &serverAddress(), 
	sizeof(serverAddress())) < 0)
    {
		returnValue = -1; 
    	std::cout<<"Error while connecting to a server"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl;  
    }
	else
	{
		std::cout << "A client connected to a server" << std::endl;
	}
	return returnValue;
}

int IOTClient::sendRequestToServer(std::string& data)
{
	int returnValue = 0;
	std::cout << "A Client sending a request ..." << std::endl;

	numberOfByteOfBuffer() = write(socketConnectToClient_,data.c_str(),data.length());
	
	if (numberOfByteOfBuffer() < 0 )
	{
		returnValue = -1; 		
		std::cout<<"Error of sending a request to a server"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl;  
	}
	else
	{
		std::cout << "Request sent to a server" << std::endl;
	}

	return returnValue;
}

int IOTClient::receiveResponseFromServer()
{
	int returnValue = 0;
	std::cout << "A Client receiving a response ..." << std::endl;

  	memset(buffer, 0, sizeof(buffer));

	numberOfByteOfBuffer() = read(socketConnectToClient_,buffer,sizeof(buffer));
    
	if (numberOfByteOfBuffer() < 0)
    {
		returnValue = -1; 	
     	std::cout<<"Fail to receive response from a server"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl;  

    }
	else
	{
		 std::cout << "Response from a server:" << std::endl;
		 std::cout << buffer << "" << std::endl;
	}
	
	return returnValue;
}

int IOTClient::closeConnection()
{
	int returnValue = 0;
	
	std::cout << "A Client closing a connection ..." << std::endl;
	
	if(close(socketConnectToClient_) < 0)
	{
		returnValue = -1; 
     	std::cout<<"Fail to close a connection with a server"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl;  
	}
	else
	{
     	std::cout<<"Connection with a server closed" << std::endl;
	}

	return returnValue;
}
