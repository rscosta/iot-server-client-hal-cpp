#include "iot_server.h"

IOTServer::IOTServer():IOTServer(0, 5){}

std::queue<Message> msgQueue;
std::vector<IOTServer::PubSubClient> pubSubList;

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
	std::cout << "Creating a server socket ..." << std::endl;

	socketListenToConnection = socket(AF_INET, SOCK_STREAM, 0);
	
	if (socketListenToConnection < 0)
	{
		returnValue = -1;		
		std::cout<<"Error while creating a server socket"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl;

	}
	else
	{
		std::cout << "A client socket created" << std::endl;

	}
	return returnValue;
}

int IOTServer::bindServerToPortNumber()
{
	int returnValue = 0;
	
	std::cout << "Binding to a local port ..." << std::endl;

    if (bind(this->socketListenToConnection,
			(struct sockaddr *) &this->serverAddress, 
					sizeof(this->serverAddress)) < 0)
    {
 		returnValue = -1;   	
		std::cout<<"Error while binding a socket"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl;
    }
	else
	{
		
		std::cout << "Bind success" << std::endl;
	}
	return returnValue;
}

int IOTServer::listenToNewClientConnection()
{
	int returnValue = 0;

	std::cout << "Listenning to a new connection..." << std::endl;
  	if (listen(socketListenToConnection, this->maxConnection) < 0)
    {
		returnValue = -1;		
    	std::cout<<"Error while listenning to a new connection"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl;
    }
	else
	{
		std::cout << "A client connected to a server" << std::endl;
	}
	return returnValue;
}

int IOTServer::acceptToMakeConnectionWithClient()
{
	int returnValue = 0;

	std::cout<< "Accepting a connection..." << std::endl;
    socketProcessAcceptedConnection = accept(socketListenToConnection,
										(struct sockaddr *)&clientAddress,
										&clientAddressLength);
     if (socketProcessAcceptedConnection < 0)
     {
		returnValue = -1;	
     	std::cout<<"Error while accepting a connection"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl;
     }
	 else
	 {
     	std::cout<<"Connection accepted" << std::endl;
		this->getClientAddress();
		this->showClientIP();
		this->showClientPort();
		this->isConnectionActive = true;

	 }
	return returnValue;
}

std::tuple<int, std::string> IOTServer::readIncomingMessageFromClient()
{
	int returnValue = 0;
	if(this->isConnectionActive)
	{
		memset(buffer, 0, sizeof(buffer));
		numberOfByteReadFromBuffer = read(socketProcessAcceptedConnection, buffer, 
											sizeof(buffer));
		if (numberOfByteReadFromBuffer < 0)
		{
			returnValue = -1;			 
			std::cout<<"Error while reading client message"
				<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl;
		    return  std::make_tuple(returnValue, "CONNFAIL");

		}
		else if(numberOfByteReadFromBuffer == 0)
		{
			std::cout << "Closing connection with client: "
									<<socketProcessAcceptedConnection<<"" << std::endl;
			this->closeAcceptedConnection();

		    return  std::make_tuple(returnValue, "CONNCLOSED");
		}
		else
		{
			std::cout<< "Data received from the client ID ["
				<< this->socketProcessAcceptedConnection <<"]: "<< buffer <<"" << std::endl;

			std::vector<std::string> row;
			std::string word;

			// used for breaking words
			std::stringstream s(buffer);

			// read every CSV column data of a row and
			// store it in a string variable, 'word'
			while (std::getline(s, word, ','))
			{
				// add all the column data
				// of a row to a vector
				row.push_back(word);
			}

			// Parse the parameter (CMD)
			std::string cmd = row[0];

			if(cmd.compare("PUBREG") == 0) //Register Publisher
			{
				// CMD parameter must be set only
				if(row.size() == 1)
				{
					//Register publisher
					PubSubClient _pubRegister;
				
					//Main publisher key
					_pubRegister.sockID = this->socketProcessAcceptedConnection;

					//Client type
					_pubRegister.clientType = PUBLISHER_TYPE;

					if(pubSubList.size() >= maxConnection)
					{
						std::cout << "[SERVER][PUBREG] - Publisher ID [" << 
							this->socketProcessAcceptedConnection << "] is not registered. Max. clients connections reached." << std::endl;
						return  std::make_tuple(returnValue, "PUBREGFAILMAXREACHED");
					}
					else
					{	
						//Add to vector
						pthread_mutex_lock(&pubSubQueueMutex);
						pubSubList.push_back(_pubRegister);
						pthread_mutex_unlock(&pubSubQueueMutex);

						std::cout << "[SERVER][PUBREG] - Publisher ID [" << this->socketProcessAcceptedConnection << "] registered succesfully." << std::endl;
						return  std::make_tuple(returnValue, "PUBREGOK");
					}
				}
				else
				{
					return std::make_tuple(returnValue, "PUBREGPARAMERROR");
				}
			}
			else if(cmd.compare("PUBREGTOP") == 0) //Register Topic to the list
			{
				// Search for the second parameter (TOPIC)
				if(row.size() == 2)
				{
					// Parse the parameter (TOPIC)
					std::string topicStr = row[1];

					pthread_mutex_lock(&pubSubQueueMutex);
					for (int i = 0; i < pubSubList.size(); i++)
					{
						// Search for the client socket ID and publisher type in the list
						if((pubSubList.at(i).sockID == this->socketProcessAcceptedConnection)&&
							(pubSubList.at(i).clientType == PUBLISHER_TYPE))
						{
							// Search for topic
				           	for (std::vector<std::string>::iterator topic = pubSubList.at(i).topics.begin(); topic != pubSubList.at(i).topics.end(); ++topic)
				            {
                				std::string stopic = *topic;
				
								// Check if topic is registered already
				                if (stopic.compare(topicStr) == 0)
								{
									pthread_mutex_unlock(&pubSubQueueMutex);
									return  std::make_tuple(returnValue, "PUBREGTOPTOPREGALREADY");
								}
							}

							// Pushes topic name to the list
							pubSubList.at(i).topics.push_back(topicStr);
							pthread_mutex_unlock(&pubSubQueueMutex);

							return std::make_tuple(returnValue, "PUBREGTOPOK");
						}
					}

					// Client is not registered.
					pthread_mutex_unlock(&pubSubQueueMutex);
				    return  std::make_tuple(returnValue, "PUBREGTOPCLIENTLISTEMPTY");
				}
				else
				{
					// Invalid parameters input	
					return std::make_tuple(returnValue, "PUBREGTOPPARAMERROR");
				}
			}
			else if(cmd.compare("PUBLISTTOP") == 0) // Return list of topics of all Publishers
			{
				// CMD parameter must be set only
				if(row.size() == 1)
				{
					std::string pubTopics;	

					pthread_mutex_lock(&pubSubQueueMutex);
					for (int i = 0; i < pubSubList.size(); i++)
					{
						// Search for publisher type in the list
						if(pubSubList.at(i).clientType == PUBLISHER_TYPE)
						{
							// Search for topics
				           	for (std::vector<std::string>::iterator topic = pubSubList.at(i).topics.begin(); topic != pubSubList.at(i).topics.end(); ++topic)
				            {
                				std::string stopic = *topic;

								pubTopics.append(stopic);

								//Append string comma in CSV result
				                if (i != (pubSubList.size()-1))
								{
									pubTopics.append(",");
								}
							}
						}
					}
					pthread_mutex_unlock(&pubSubQueueMutex);

					if(pubTopics.size() > 0)
					{	
						std::string formatResult;

						formatResult.append("PUBLISTTOPOK,"); // Messaging processing result
						formatResult.append(std::to_string(pubTopics.size())); // Numbers of publishers topics list
						formatResult.append(",");
						formatResult.append(pubTopics); //List of publishers topics
					
						std::cout << "[SERVER][PUBLISTTOP] - publisher topics found: (" << pubTopics << ")" << std::endl;						returnValue = 0;
						
						return std::make_tuple(returnValue, formatResult);
					}
					else
					{
						// There is no publisher with topics available.
						return  std::make_tuple(returnValue, "PUBLISTTOPCLIENTLISTEMPTY");
					}
				}
				else
				{
					// Invalid parameters input	
					return std::make_tuple(returnValue, "PUBLISTTOPPARAMERROR");

				}
			}
			else if(cmd.compare("SENDPAYLOAD") == 0)
			{
				// Search for the second & third parameters (TOPIC, MESSAGE)
				if(row.size() == 3)
				{
					// Parse the second parameter (TOPIC)
					std::string topicMsg = row[1];

					// Parse the third parameter (MESSAGE)
					std::string strMsg = row[2];

					pthread_mutex_lock(&pubSubQueueMutex);
					for (int i = 0; i < pubSubList.size(); i++)
					{
						// Search for the client socket ID in the list
						if(pubSubList.at(i).sockID == this->socketProcessAcceptedConnection)
						{
							std::cout << "[SERVER][SENDPAYLOAD] - data:" << strMsg << " will be injected into topic:" 
										<< topicMsg << ". But Searching at first for this topic into the Client's topic list." << std::endl;

							// Search for topic
				           	for (std::vector<std::string>::iterator topic = pubSubList.at(i).topics.begin(); topic != pubSubList.at(i).topics.end(); ++topic)
				            {
                				std::string stopic = *topic;
				
				                if (stopic.compare(topicMsg) == 0)
								{
									Message clientMsg(topicMsg, strMsg);

									std::cout << "[SERVER][SENDPAYLOAD] - data:" << strMsg << " will be injected into topic now into" 
										<< topicMsg << "." << std::endl;

									// Push message to message Queue 
									receive(clientMsg);

									std::cout << "[SERVER][SENDPAYLOAD] - data:" << strMsg << " injected into topic:" 
												<< topicMsg << std::endl;

									pthread_mutex_unlock(&pubSubQueueMutex);
								    return  std::make_tuple(returnValue, "SENDPAYLOADOK");
								}
							}

							pthread_mutex_unlock(&pubSubQueueMutex);
							return  std::make_tuple(returnValue, "SENDPAYLOADTOPNOTFOUND");
						}
					}

					pthread_mutex_unlock(&pubSubQueueMutex);
				    return  std::make_tuple(returnValue, "SENDPAYLOADCLIENTLISTEMPTY");
				}
				else
				{
					return std::make_tuple(returnValue, "SENDPAYLOADPARAMERROR");
				}
			}
			else if(cmd.compare("SUBREG") == 0) //Register Subscriber
			{
				// CMD parameter must be set only
				if(row.size() == 1)
				{
					// register subscriber
					PubSubClient _subRegister;
				
					//Main subscriber key
					_subRegister.sockID = this->socketProcessAcceptedConnection;

					//Client type
					_subRegister.clientType = SUBSCRIBER_TYPE;

					if(pubSubList.size() >= maxConnection)
					{
						std::cout << "[SERVER][SUBREG] - Subscriber ID [" << 
							this->socketProcessAcceptedConnection << "] is not registered. Max. clients connections reached." << std::endl;
						return  std::make_tuple(returnValue, "SUBREGFAILMAXREACHED");
					}
					else
					{	
						//Add to vector
						pthread_mutex_lock(&pubSubQueueMutex);
						pubSubList.push_back(_subRegister);
						pthread_mutex_unlock(&pubSubQueueMutex);

						std::cout << "[SERVER][SUBREG] - Subscriber ID [" << this->socketProcessAcceptedConnection << "] registered succesfully." << std::endl;
						return  std::make_tuple(returnValue, "SUBREGOK");
					}
				}
				else
				{
					return std::make_tuple(returnValue, "SUBREGPARAMERROR");
				}
			}
			else if(cmd.compare("SUBLISTENTOP") == 0) //Register Subscriber Topic filter
			{
				// Search for the second parameter (TOPIC)
				if(row.size() == 2)
				{
					// Parse the parameter (TOPIC)
					std::string topicStr = row[1];

					pthread_mutex_lock(&pubSubQueueMutex);
					for (int i = 0; i < pubSubList.size(); i++)
					{
						// Search for the client socket ID and subscriber type in the list
						if((pubSubList.at(i).sockID == this->socketProcessAcceptedConnection)&&
							(pubSubList.at(i).clientType == SUBSCRIBER_TYPE))
						{
							// Search for topic
				           	for (std::vector<std::string>::iterator topic = pubSubList.at(i).topics.begin(); topic != pubSubList.at(i).topics.end(); ++topic)
				            {
                				std::string stopic = *topic;
				
								// Check if topic is registered already
				                if (stopic.compare(topicStr) == 0)
								{
									pthread_mutex_unlock(&pubSubQueueMutex);
									return  std::make_tuple(returnValue, "SUBLISTENTOPREGALREADY");
								}
							}

							// Pushes topic name to the list
							pubSubList.at(i).topics.push_back(topicStr);
							pthread_mutex_unlock(&pubSubQueueMutex);

							std::cout << "[SERVER][SUBLISTENTOP] - topic:"<< topicStr << " registered to Subscriber ID [" << socketListenToConnection << "]" << std::endl;						returnValue = 0;

							return std::make_tuple(returnValue, "SUBLISTENTOPOK");
						}
					}

					// Client is not registered.
					pthread_mutex_unlock(&pubSubQueueMutex);
				    return  std::make_tuple(returnValue, "SUBLISTENTOPCLIENTLISTEMPTY");
				}
				else
				{
					// Invalid parameters input	
					return std::make_tuple(returnValue, "PUBREGTOPPARAMERROR");
				}
			}
			else if(cmd.compare("SUBUNREGTOP") == 0) //Remove a topic filter of a subscriber
			{
				// Search for the second parameter (TOPIC)
				if(row.size() == 2)
				{
					// Parse the parameter (TOPIC)
					std::string topicStr = row[1];

					pthread_mutex_lock(&pubSubQueueMutex);
					for (int i = 0; i < pubSubList.size(); i++)
					{
						// Search for the client socket ID and subscriber type in the list
						if((pubSubList.at(i).sockID == this->socketProcessAcceptedConnection)&&
							(pubSubList.at(i).clientType == SUBSCRIBER_TYPE))
						{
                            // Search for topic
				           	for (std::vector<std::string>::iterator topic = pubSubList.at(i).topics.begin(); topic != pubSubList.at(i).topics.end(); ++topic)
				            {
                				std::string stopic = *topic;
				
								// Check if topic is registered already
				                if (stopic.compare(topicStr) == 0)
								{
									// Removes Pushes topic name to the list
									pubSubList.at(i).topics.erase(topic);
									
									std::cout << "[SERVER][SUBUNREGTOP] - topic:"<< topicStr << " unregistered from Subscriber ID [" << socketListenToConnection << "]" << std::endl;

									pthread_mutex_unlock(&pubSubQueueMutex);
					
									return std::make_tuple(returnValue, "SUBUNREGTOPOK");
								}
							}
							
							pthread_mutex_unlock(&pubSubQueueMutex);
							return  std::make_tuple(returnValue, "SUBUNREGTOPTOPNOTFOUND");
						}
					}

					// Client is not registered.
					pthread_mutex_unlock(&pubSubQueueMutex);
				    return  std::make_tuple(returnValue, "SUBUNREGTOPCLIENTLISTEMPTY");
				}
				else
				{
					// Invalid parameters input	
					return std::make_tuple(returnValue, "SUBUNREGTOPPARAMERROR");
				}
			}
			
	    	return std::make_tuple(returnValue, "INVALIDCMD");
		}		
	}

    return std::make_tuple(-3, "CONNERROR");
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
											&message[0], 1024);
				if (numberOfByteReadFromBuffer < 0)
				{
					returnValue = -1;		
					std::cout<<"Fail to send back message to the client"
						<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl;
					
				}			
				break;
			case 400:
				std::cout<<"Connection with client closed." << std::endl;			
			
			default:
				std::cout<<"Unknown sendResponseToClient ERROR." << std::endl;

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
												&message[0], 1024);
					if (numberOfByteReadFromBuffer < 0)
					{
						returnValue = -1;		
						std::cout<<"Fail to send back message to the client"
							<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl;
						
					}			
					break;
				case 400:
					std::cout<<"Connection with client closed." << std::endl;
				
				default:
					std::cout<<"Unknown sendResponseToClient ERROR." << std::endl;

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
			returnValue = -1;	
			std::cout<<"Fail to get server port number from getsockname"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl;						
	}
	else
	{
		returnValue = ntohs(serverAddress.sin_port);  // get the port number
		if(returnValue < 0)
		{
			returnValue = -1;	
			std::cout<<"ntos error with sin_port"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl;					
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
       	returnValue = -1; 
        std::cout << "unable to convert IP from binary to text "
					<<"dotted-decimal format"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl; 
    }
	return returnValue;

}

int IOTServer::showClientPort()
{
	int returnValue = 0;
	this->clientPortNumber = ntohs(this->clientAddress.sin_port);
    if(this->clientPortNumber < 0)
    {
       	returnValue = -1; 
        std::cout << "unable to convert Port Number from network to host order "
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl;    
    }
	else
	{
		std::cout << "Client Port Number: ["<< this->clientPortNumber<<"]" << std::endl;

	}
	return returnValue;
}

int IOTServer::showClientIP()
{
	int returnValue = 0;
	std::cout << "Client IP: ["<< this->clientIPv4<<"]" << std::endl;
	return returnValue;
}

int IOTServer::showServerPort()
{
	int returnValue = 0;
	this->getPort();
	std::cout << "Server Port Number: ["<< this->serverPortNumber<<"]" << std::endl;
	return returnValue;
}

int IOTServer::showServerIP()
{
	int returnValue = 0;
	if( getLocalAddress(this->serverIPv4) < 0)
	{
       	returnValue = -1; 
        std::cout << "Fail to get server address from getLocalAddress"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl; 
	}
	else
	{
		std::cout << "Server IP: ["<< this->serverIPv4<<"]" << std::endl;
	}
	return returnValue;
}

int IOTServer::showMaxConnection()
{
	int returnValue = 0;
	std::cout << "Server max connection: ["<< this->maxConnection<<"]" << std::endl;
	return returnValue;
}

int IOTServer::closeAcceptedConnection()
{
	int returnValue = 0;

	std::cout<< "A Server closing an accepted connection ..." << std::endl;
	
	if(close(socketProcessAcceptedConnection) < 0)
	{
       	returnValue = -1; 
     	std::cout<<"Fail to close a connection with a server"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl; 

	}
	else
	{
     	std::cout <<"Accepted connection closed" << std::endl;
		 this->isConnectionActive = false;

	}
	return returnValue;
}

bool IOTServer::isClientConnectionAlive()
{
	return this->isConnectionActive;
}

int IOTServer::closeListenningSocket()
{
	int returnValue = 0;

	std::cout << "A Server stopping listen to a new connection ..." << std::endl;

	if(close(socketListenToConnection) < 0)
	{
		returnValue = -1; 
     	std::cout<<"Fail to close a listenning socket"
			<<"[ERROR]["<<strerror(errno)<<"]["<<returnValue<<"]" << std::endl;  
	

	}
	else
	{
     	std::cout<<"Listenning socket closed" << std::endl;

		std::cout << "A server stopped listen to a new connection" << std::endl;	
	}

	return returnValue;
}

std::string IOTServer::getCurrentTime()
{
	return std::string(" ");
}

void IOTServer::processQueue()
{
	pthread_mutex_lock(&srvQueueMutex);

    if (!msgQueue.empty())
    {
        Message tmpMsg = msgQueue.front();
        msgQueue.pop();
		pthread_mutex_unlock(&srvQueueMutex);

		pthread_mutex_lock(&pubSubQueueMutex);
		for (int i = 0; i < pubSubList.size(); i++)
        {
            for (std::vector<std::string>::iterator topic = pubSubList.at(i).topics.begin(); topic != pubSubList.at(i).topics.end(); ++topic)
            {
                std::string stopic = *topic;

                if (stopic.compare(tmpMsg.getTopic()) == 0)
				{
			        pubSubList.at(i).msgQueuePubSub.push(tmpMsg);
				}
			}
        }
		pthread_mutex_unlock(&pubSubQueueMutex);
	}
	pthread_mutex_unlock(&srvQueueMutex);
}

void IOTServer::receive(const Message &newMessage)
{
	pthread_mutex_lock(&srvQueueMutex);
    msgQueue.push(newMessage);
	pthread_mutex_unlock(&srvQueueMutex);
}

int IOTServer::sendMessagesToClientFromQueue()
{
	int result = 0;

	pthread_mutex_lock(&pubSubQueueMutex);

	if(pubSubList.size() > 0)
	{
		for (int i = 0; i < pubSubList.size(); i++)
		{
			if(pubSubList.at(i).sockID == this->socketProcessAcceptedConnection)
			{
				if(!pubSubList.at(i).msgQueuePubSub.empty())
				{
					Message msg = pubSubList.at(i).msgQueuePubSub.front();

					pubSubList.at(i).msgQueuePubSub.pop();

					std::cout << "Message dispatched >>>>>>>:" << msg.getMessage() << std::endl;
					
					sendResponseToClient(msg.getMessage(), 200);
				}
			}
		}
	}

	pthread_mutex_unlock(&pubSubQueueMutex);

	return result;
}
