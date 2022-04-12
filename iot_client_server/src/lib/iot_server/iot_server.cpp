#include "iot_server.h"


IOTServer::IOTServer():IOTServer(0, 5){}

IOTServer::IOTServer(unsigned short _portNumber_, unsigned short _max_connection_):
serverPortNumber(_portNumber_), maxConnection(_max_connection_)
{
	memset(&serverAddress, 0, sizeof(serverAddress));
	memset(&clientAddress, 0, sizeof(clientAddress));

	this->serverAddressLength = sizeof(this->serverAddress);
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;
    this->serverAddress.sin_port = htons(this->serverPortNumber);
	clientAddressLength = sizeof(clientAddress);
	this->isConnectionActive = false;
}

int IOTServer::createServerForBindAndListen()
{
	this->showMaxConnection();
	int returnValue = 0;
	std::cout << "Creating a server socket ...\n";

	socketListenToConnection = socket(AF_INET, SOCK_STREAM, 0);
	
	if (socketListenToConnection < 0)
	{
		returnValue = -100000;		
		std::cout<<"Error while creating a server socket"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";

	}
	else
	{
		
		std::cout << "A client socket created\n";

	}
	return returnValue;
}

int IOTServer::bindServerToPortNumber()
{
	int returnValue = 0;
	
	std::cout << "Binding to a local port ...\n";

    if (bind(this->socketListenToConnection,
			(struct sockaddr *) &this->serverAddress, 
					sizeof(this->serverAddress)) < 0)
    {
 		returnValue = -100001;   	
		std::cout<<"Error while binding a socket"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";
    }
	else
	{
		
		std::cout << "Bind success\n";
	}
	return returnValue;
}

int IOTServer::listenToNewClientConnection()
{
	int returnValue = 0;

	std::cout << "Listenning to a new connection...\n";
  	if (listen(socketListenToConnection, this->maxConnection) < 0)
    {
		returnValue = -100002;		
    	std::cout<<"Error while Listenning to a new connection"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";
    }
	else
	{
		std::cout << "A client connected to a server\n";
	}
	return returnValue;
}

int IOTServer::acceptToMakeConnectionWithClient()
{
	int returnValue = 0;

	std::cout<< "Accepting a connection...\n";
    socketProcessAcceptedConnection = accept(socketListenToConnection,
										(struct sockaddr *)&clientAddress,
										&clientAddressLength);
     if (socketProcessAcceptedConnection < 0)
     {
		returnValue = -100003;	
     	std::cout<<"Error while accepting a connection"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";
     }
	 else
	 {
     	std::cout<<"Connection accepted\n";
		this->getClientAddress();
		this->showClientIP();
		this->showClientPort();
		this->isConnectionActive = true;

	 }
	return returnValue;
}

int IOTServer::readIncomingMessageFromClient()
{
	int returnValue = 0;
	if(this->isConnectionActive)
	{
		memset(buffer, 0, sizeof(buffer));
		numberOfByteReadFromBuffer = read(socketProcessAcceptedConnection, buffer, 
											sizeof(buffer));
		if (numberOfByteReadFromBuffer < 0)
		{
			returnValue = -100004;			 
			std::cout<<"Error while reading client message"
				<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";
		}
		else if(numberOfByteReadFromBuffer == 0)
		{
			std::cout << "Closing connection with client: "
									<<socketProcessAcceptedConnection<<"\n";
			this->closeAcceptedConnection();
		}
		else
		{
    		// Parse json
			json::jobject jClientBuffer = json::jobject::parse(buffer);
    		std::string reqTypeStr = jClientBuffer["requestType"].as_string();

			//Check request type
			if(reqTypeStr.compare("PUBLISH") == 0)
			{
    			std::string topicStr = jClientBuffer["topic"].as_string();
    			std::string devTypeStr = jClientBuffer["deviceType"].as_string();
    			int value = 0;//jClientBuffer["value"].as_integer();

				//std::cout << "[SERVER]- topic:" << topicStr << "request Type:" << reqTypeStr << "device type:" << devTypeStr << "temperature:" << value << std::endl;
						
				// Serialize in JSON format	
				json::jobject jTempSensor;
				jTempSensor["topic"] = topicStr;
				jTempSensor["deviceType"] = devTypeStr;
				jTempSensor["value"] = value;  
			
				//std::cout << "[SERVER]- " << jTempSensor.pretty() << std::endl;

				// Prints JSON stream
				std::string tempSensorRes(jTempSensor.pretty());
				
				Message client(topicStr, tempSensorRes);
				
				// Push buffer to a topic 
				receive(client);

			}
			else if(reqTypeStr.compare("REGISTER") == 0)
			{
				// register subscriber
    			sSubscriber subRegister;
			
				subRegister.tcpSocketHandle = socketListenToConnection;

				subscribe(subRegister);	

				std::cout << "[SERVER][REGISTER] - Subscriber[" << socketListenToConnection << "] registered." << std::endl;
			}
			else if(reqTypeStr.compare("TOPIC_LISTEN") == 0)
			{
    			std::string newTopic = jClientBuffer["topic"].as_string();

				//returnValue = -100005;			 

				for (int i = 0; i < subscriberList.size(); i++)
				{
					if(subscriberList.at(i).tcpSocketHandle == socketListenToConnection)
					{
						subscriberList.at(i).topics.push_back(newTopic);

						std::cout << "[SUBSCRIBER][TOPIC_LISTEN] - newTopic:"<< newTopic << "added to client: " << socketListenToConnection << std::endl;
					
						returnValue = 0;
					}
				}
			}
			else if(reqTypeStr.compare("GET_DATA") == 0)
			{
    			//std::string subTopic = jClientBuffer["topic"].as_string();

				for (int i = 0; i < subscriberList.size(); i++)
				{
					if(subscriberList.at(i).tcpSocketHandle == socketListenToConnection)
					{
 						Message msg = subscriberList.at(i).msgQueue.front();
        				
						subscriberList.at(i).msgQueue.pop();
        				
						std::cout << msg.getMessage() << std::endl;
 						
						std::cout << "[SUBSCRIBER][GET_DATA] topic:"<< msg.getTopic() << " message: " << msg.getMessage() << std::endl;
					
						returnValue = 0;
					}
				}
			}

			std::cout<< "Data received from the client "
				<< socketProcessAcceptedConnection <<": "<< buffer <<"\n";
		}		
	}

	return returnValue;
}

int IOTServer::sendResponseToClient(std::string &message, int status)
{
	int returnValue = 0;
	if(this->isConnectionActive)
		{
			switch (status)
			{
			case 200:
				numberOfByteReadFromBuffer = write(socketProcessAcceptedConnection,
											&message[0],18);
				if (numberOfByteReadFromBuffer < 0)/////////////
				{
					returnValue = -100006;		
					std::cout<<"Fail to send back message to the client"
						<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";
					
				}			
				break;
			case 400:
				std::cout<<"[Function 1] - Connection with client closed.\n";			
			
			default:
				std::cout<<"Unknown sendResponseToClient ERROR.\n";

				break;
			}
	}
	
	return returnValue;
}

int IOTServer::sendResponseToClient(std::string &&message, int status)
{
	int returnValue = 0;
	if(this->isConnectionActive)
	{
			switch (status)
			{
				case 200:
					numberOfByteReadFromBuffer = write(socketProcessAcceptedConnection,
												&message[0],18);
					if (numberOfByteReadFromBuffer < 0)
					{
						returnValue = -100006;		
						std::cout<<"Fail to send back message to the client"
							<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";
						
					}			
					break;
				case 400:
					std::cout<<"[Function 2] - Connection with client closed.\n";
				
				default:
					std::cout<<"Unknown sendResponseToClient ERROR.\n";

					break;
			}
	}
	
	return returnValue;
}

int IOTServer::getPort()
{
	int returnValue = 0;

    if( getsockname(socketListenToConnection, (struct sockaddr *)&serverAddress, 
		&serverAddressLength) < 0)
		{
			returnValue = -100007;	
			std::cout<<"Fail to get server port number from getsockname"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";						
	}
	else
	{
		returnValue = ntohs(serverAddress.sin_port);  // get the port number
		if(returnValue < 0)
		{
			returnValue = -100008;	
			std::cout<<"ntos error with sin_port"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";					
		}
		else
		{
			this->serverPortNumber = (unsigned short) returnValue;
		}
	}
    
    return returnValue;
}

int IOTServer::getClientAddress()
{
	int returnValue = 0;
    if(inet_ntop(AF_INET, &this->clientAddress.sin_addr, this->clientIPv4, 
				INET_ADDRSTRLEN) == NULL)
    {
       	returnValue = -100009; 
        std::cout << "unable to convert IP from binary to text "
					<<"dotted-decimal format"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n"; 
    }
	return returnValue;

}

int IOTServer::showClientPort()
{
	int returnValue = 0;
	this->clientPortNumber = ntohs(this->clientAddress.sin_port);
    if(this->clientPortNumber < 0)
    {
       	returnValue = -100010; 
        std::cout << "unable to convert Port Number from network to host order "
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";    
    }
	else
	{
		std::cout << "Client Port Number: ["<< this->clientPortNumber<<"]\n";

	}
	return returnValue;

}

int IOTServer::showClientIP()
{
	int returnValue = 0;
	std::cout << "Client IP: ["<< this->clientIPv4<<"]\n";
	return returnValue;
}

int IOTServer::showServerPort()
{
	int returnValue = 0;
	this->getPort();
	std::cout << "Server Port Number: ["<< this->serverPortNumber<<"]\n";
	return returnValue;
}

int IOTServer::showServerIP()
{
	int returnValue = 0;
	if( getLocalAddress(this->serverIPv4) < 0)
	{
       	returnValue = -100011; 
        std::cout << "Fail to get server address from getLocalAddress"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n"; 
	}
	else
	{
		std::cout << "Server IP: ["<< this->serverIPv4<<"]\n";
	}
	return returnValue;
}

int IOTServer::showMaxConnection()
{
	int returnValue = 0;
	std::cout << "Server max connection: ["<< this->maxConnection<<"]\n";
	return returnValue;
}

int IOTServer::closeAcceptedConnection()
{
	int returnValue = 0;
	std::cout<< "A Server closing an accpeted connection ...\n";
	if(close(socketProcessAcceptedConnection) < 0)
	{
       	returnValue = -100012; 
     	std::cout<<"Fail to close a connection with a server"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n"; 

	}
	else
	{
     	std::cout <<"Accepted connection closed\n";
		 this->isConnectionActive = false;

	}
	return returnValue;
}

int IOTServer::closeListenningSocket()
{
	int returnValue = 0;


		std::cout << "A Server stopping listen to a new connection ...\n";
		if(close(socketListenToConnection) < 0)
		{
		returnValue = -100013; 
     	std::cout<<"Fail to close a listenning socket"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]\n";  
	

		}
		else
		{
     	std::cout<<"Listenning socket closed\n";
		std::cout << "A server stopped listen to a new connection\n";	

		}
	return returnValue;
}

std::string IOTServer::getCurrentTime()
{
	return std::string(" ");
}

void IOTServer::processQueue()
{
    while (!msgQueue.empty())
    {
        Message tmpMsg = msgQueue.front();
        msgQueue.pop();
        for (int i = 0; i < subscriberList.size(); i++)
        {
            for (std::vector<std::string>::iterator topic = subscriberList.at(i).topics.begin(); topic != subscriberList.at(i).topics.end(); ++topic)
            {
                std::string stopic = *topic;
                if (stopic.compare(tmpMsg.getTopic()) == 0)
                    subscriberList.at(i).msgQueue.push(tmpMsg);
            }
        }
    }
}

void IOTServer::subscribe(sSubscriber subscribe)
{
    subscriberList.push_back(subscribe);
}

void IOTServer::receive(const Message &newMessage)
{
    msgQueue.push(newMessage);
}
