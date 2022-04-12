#ifndef _IOT_CLIENT_H_
#define _IOT_CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <time.h>

#include <iostream>
#include <ctime>
#include <string>
#include <tuple>

class IOTClient
{
public:

	IOTClient(char *_serverIP_, unsigned short _serverPort_);
	int createClientForConnection();
	int connectClientToServer();
	int sendRequestToServer(std::string& data);
	int receiveResponseFromServer();
	int closeConnection();
	std::tuple <std::string, std::string> getCurrentTime();

	// Setter and Getter socketConnectToClient
	auto socketConnectToClient() const& -> const int& { return socketConnectToClient_; }
	auto socketConnectToClient() &      -> int&       { return socketConnectToClient_; }
	auto socketConnectToClient() &&     -> int&&      { return std::move(socketConnectToClient_); }

	// Setter and Getter serverPortNumber
	auto serverPortNumber() const& -> const unsigned short& { return serverPortNumber_; }
	auto serverPortNumber() &      -> unsigned short&       { return serverPortNumber_; }
	auto serverPortNumber() &&     -> unsigned short&&      { return std::move(serverPortNumber_); }

	// Setter and Getter numberOfByteOfBuffer
	auto numberOfByteOfBuffer() const& -> const int& { return numberOfByteOfBuffer_; }
	auto numberOfByteOfBuffer() &      -> int&       { return numberOfByteOfBuffer_; }
	auto numberOfByteOfBuffer() &&     -> int&&      { return std::move(numberOfByteOfBuffer_); }

	// Setter and Getter socketConnectToClient
	auto serverAddress() const& -> const sockaddr_in& { return serverAddress_; }
	auto serverAddress() &      -> sockaddr_in&       { return serverAddress_; }
	auto serverAddress() &&     -> sockaddr_in&&      { return std::move(serverAddress_); }

private:
	int socketConnectToClient_;
	unsigned short serverPortNumber_;
	int numberOfByteOfBuffer_;
	struct sockaddr_in serverAddress_;
	struct hostent *serverIP_;
	char buffer[2048];
};

#endif /* _IOT_CLIENT_H_ */
