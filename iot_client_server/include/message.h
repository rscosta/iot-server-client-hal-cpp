#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <string>

/**
 * @brief  Message Class definition
 * 
 */
class Message
{
public:

    Message(std::string topic, std::string msg) : _topic(topic), _msg(msg){};

    std::string getMessage(){ return _msg; };

    std::string getTopic(){ return _topic; };

private:
    std::string _topic;
    std::string _msg;
};
#endif /* _MESSAGE_H_ */

