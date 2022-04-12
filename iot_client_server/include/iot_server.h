#ifndef _IOT_SERVER_H_
#define _IOT_SERVER_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstddef>
#include <pthread.h>

#include <tuple>
#include <string>
#include <queue>
#include <vector>
#include <iterator>
#include <map>

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

    struct sSubscriber
    {
        std::vector<std::string> topics;
        std::queue<Message> msgQueue;
        int tcpSocketHandle;
    };

	IOTServer();
	IOTServer(unsigned short _portNumber_, unsigned short _max_connection_);

	int createServerForBindAndListen();
	int bindServerToPortNumber();
	int listenToNewClientConnection();
	int acceptToMakeConnectionWithClient();
	int sendResponseToClient(std::string &message, int status);
	int sendResponseToClient(std::string &&message, int status);
	int readIncomingMessageFromClient();

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
	void subscribe(sSubscriber subscribe);
	void receive(const Message &newMessage);

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
	char buffer[2048];
	std::string serverIPv4;
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
    std::queue<Message> msgQueue;
    std::vector<sSubscriber> subscriberList;
};

#endif /* _IOT_SERVER_H_ */
