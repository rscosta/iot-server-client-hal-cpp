#ifndef _IOT_SERVER_H_
#define _IOT_SERVER_H_

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <tuple>
#include <string>
#include <queue>
#include <vector>
#include <iterator>
#include <map>
#include <memory>
#include <sstream>

#include "message.h"
#include "custom_json.h"
#include "utils.h"

/**
 * Implementation of a server
 * This server uses TCP Socket for multiple
 * clients.
 */
class IOTServer
{
public:
	enum client_t
	{
		PUBLISHER_TYPE,
		SUBSCRIBER_TYPE,
		WEBSERVER_TYPE
	};

    struct PubSubClient
    {
        std::vector<std::string> topics;
        std::queue<Message> msgQueuePubSub;
        int sockID;
		client_t clientType;
    };

	IOTServer();
	IOTServer(unsigned short _portNumber_, unsigned short _max_connection_);

	int createServerForBindAndListen();
	int bindServerToPortNumber();
	int listenToNewClientConnection();
	int acceptToMakeConnectionWithClient();
	int sendResponseToClient(std::string &message, int status);
	int sendResponseToClient(std::string &&message, int status);
	std::tuple<int, std::string> readIncomingMessageFromClient();
	int getPort();
	int getClientAddress();
	int showMaxConnection();
	int showServerPort();
	int showServerIP();
	int showClientPort();
	int showClientIP();
	int closeAcceptedConnection();
	int closeListenningSocket();
	std::string getCurrentTime();
	void processQueue();
	void receive(const Message &newMessage);
	int sendMessagesToClientFromQueue();
	bool isClientConnectionAlive();

private:
	int socketListenToConnection {0};
	int socketProcessAcceptedConnection {0};
	bool isConnectionActive {false};
	unsigned short maxConnection {0};
	unsigned short serverPortNumber {0};
	unsigned short  clientPortNumber {0};
	ssize_t numberOfByteReadFromBuffer {0};
	char clientIPv4[INET_ADDRSTRLEN +1];
	socklen_t clientAddressLength;
	socklen_t serverAddressLength;
	char buffer[1024];
	std::string serverIPv4;
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	pthread_mutex_t srvQueueMutex;
	pthread_mutex_t pubSubQueueMutex;
};

#endif /* _IOT_SERVER_H_ */
