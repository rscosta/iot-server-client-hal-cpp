#include "iot_client.h"

IOTClient::IOTClient(char *_serverIP_, unsigned short _serverPort_)
{
	std::cout<<"Client initializing ...\n";

	serverPortNumber() = _serverPort_;
	this->createClientForConnection();

	serverIP_ = gethostbyname(_serverIP_);
	if (serverIP_ == NULL)
	{
		std::cout<<"Error host not found"
					<<strerror(h_errno)<<"\n";

	}
	else
	{
		std::cout<<"Client initialized\n";
	}

	this->connectClientToServer();
}

int IOTClient::createClientForConnection()
{
	int returnValue = 0;

	std::cout << "Creating a client socket ...\n";

	socketConnectToClient_ = socket(AF_INET, SOCK_STREAM, 0);
	if (socketConnectToClient_ < 0)
	{
		returnValue = -200000; 
		std::cout <<"Error while creating a client socket"
	<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n"; 
	}
	else
	{
		std::cout << "A client socket created\n";

	}
	return returnValue;
}

int IOTClient::connectClientToServer()
{
	int returnValue = 0;
	std::cout << "Connecting to a server ...\n";

	bzero((char *) &serverAddress(), sizeof(serverAddress()));

    serverAddress().sin_family = AF_INET;

    bcopy((char *)serverIP_->h_addr, (char *)&serverAddress().sin_addr.s_addr,
	serverIP_->h_length);

    serverAddress().sin_port = htons(serverPortNumber());

    if (connect(socketConnectToClient_,(struct sockaddr *) &serverAddress(), 
	sizeof(serverAddress())) < 0)
    {
		returnValue = -200001; 
    	std::cout<<"Error while connecting to a server"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";  

    }
	else
	{
		std::cout << "A client connected to a server\n";
	}
	return returnValue;
}

int IOTClient::sendRequestToServer(std::string& data)
{
	int returnValue = 0;
	std::cout << "A Client sending a request ...\n";
	//std::string aux = clock.currentDateTime();
	//std::string data = std::get<1>(getCurrentTime());

	numberOfByteOfBuffer() = write(socketConnectToClient_,data.c_str(),data.length());
	if (numberOfByteOfBuffer() < 0 )
	{
		returnValue = -200002; 		
		std::cout<<"Error of sending a request to a server"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";  
	}
	else
	{
		std::cout << "Request sent to a server\n";

	}
	return returnValue;

}

int IOTClient::receiveResponseFromServer()
{
	int returnValue = 0;
	std::cout << "A Client receiving a response ...\n";

    bzero(buffer,1024);
     numberOfByteOfBuffer() = read(socketConnectToClient_,buffer,1023);
    if (numberOfByteOfBuffer() < 0)
     {
		returnValue = -200003; 	
     	std::cout<<"Fail to receive response from a server"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";  

     }
	 {
		 std::cout << "Response from a server\n";
		 std::cout << buffer << "\n";
	 }
	return returnValue;
}

int IOTClient::closeConnection()
{
	int returnValue = 0;
	std::cout << "A Client closing a connection ...\n";
	if(close(socketConnectToClient_) < 0)
	{
		returnValue = -200004; 
     	std::cout<<"Fail to close a connection with a server"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";  

	}
	else
	{
     	std::cout<<"Connection with a server closed\n";

	}
	return returnValue;
}
