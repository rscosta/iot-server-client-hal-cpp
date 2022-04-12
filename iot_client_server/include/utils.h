#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <cstring> 
#include <errno.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<string.h>
#include<netinet/in.h>
#include <cstring>
#include <tuple>
#include <string>
#include <ctime>

int getLocalAddress(std::string& myIP);
std::tuple <std::string, std::string> getCurrentTime();

#endif /*_UTILS_H_ */