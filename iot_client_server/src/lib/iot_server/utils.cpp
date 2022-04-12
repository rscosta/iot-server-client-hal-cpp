
#include "utils.h"

int getLocalAddress(std::string& myIP)
{
    const char* googleDNSServerIPAddress = "8.8.8.8";
    int googleDNSServerPortNumber = 53;

    struct sockaddr_in googleDNServerAddress;
    int socketToAcessGoogleDNSServer = socket(AF_INET, SOCK_DGRAM, 0);
    int returnValue = 0;
    //Socket could not be created
    if((socketToAcessGoogleDNSServer = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        returnValue = errno;
        std::cout << "socket to acess Google DNS Server [create][ERROR]["<<strerror(errno)<<"]\n";
        return returnValue;
        
    }

    memset(&googleDNServerAddress, 0, sizeof(googleDNServerAddress));
    googleDNServerAddress.sin_family = AF_INET;
    googleDNServerAddress.sin_addr.s_addr = inet_addr(googleDNSServerIPAddress);
    googleDNServerAddress.sin_port = htons(googleDNSServerPortNumber);

    if (connect(socketToAcessGoogleDNSServer, (const struct sockaddr*)&googleDNServerAddress, 
    sizeof(googleDNServerAddress)) < 0)
    {
        returnValue = errno;
        std::cout << "connect to Google DNS Server[ERROR]["<<strerror(errno)<<"]\n";
        close(socketToAcessGoogleDNSServer);
        return returnValue;
  
    }

    struct sockaddr_in localHostIPName;
    socklen_t localHostIPNameLength = sizeof(localHostIPName);

    if (getsockname(socketToAcessGoogleDNSServer, (struct sockaddr*)&localHostIPName, 
    &localHostIPNameLength) < 0)
    {
        returnValue = errno;
        std::cout << "unable to get local IP through getsockname[ERROR]["<<strerror(errno)<<"]\n";
        close(socketToAcessGoogleDNSServer);
        return returnValue;
    }      
    char bufferIPv4[INET_ADDRSTRLEN +1];
    //const char* p = inet_ntop(AF_INET, &localHostIPName.sin_addr, bufferIPv4, INET_ADDRSTRLEN);

    if(inet_ntop(AF_INET, &localHostIPName.sin_addr, bufferIPv4, INET_ADDRSTRLEN) == NULL)
    {
        returnValue = errno;
        std::cout << "unable to convert IP from binary to text dotted-decimal format[ERROR]["
        <<strerror(errno)<<"]\n";
        close(socketToAcessGoogleDNSServer);
        return returnValue;      
    }

    //inet_ntop

    
  
    myIP = bufferIPv4;  
       
    close(socketToAcessGoogleDNSServer);
        
    return 0;
       
}

std::tuple <std::string, std::string> getCurrentTime()
{
    std::time_t now = std::time(NULL);
    std::tm * ptm = std::localtime(&now);
    char buffer1[32], buffer2[32];
    // Format: Mo, 15.06.2009 20:20:00
    std::strftime(buffer1, 32, "%d_%m_%Y_%H_%M_%S_", ptm);
    std::strftime(buffer2, 32, "%H:%M:%S", ptm);
	return std::make_tuple(std::string(buffer1), std::string(buffer2));
}
