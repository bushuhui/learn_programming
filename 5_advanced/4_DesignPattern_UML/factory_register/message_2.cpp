#include <iostream>
#include "factory.h"

class Message2 : public Message
{
public:

    Message2()
    {
        std::cout << "message2" << std::endl;
    }


    ~Message2()
    {
    }

    void foo()
    {
        std::cout << "message2 " <<b<< std::endl;
    }

private:
    int b = 0;
};

REGISTER_MESSAGE(Message2,"message2");
