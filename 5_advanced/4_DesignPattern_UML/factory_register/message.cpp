#include <iostream>
#include "factory.h"

class Message1 : public Message
{
public:

    Message1()
    {
        std::cout << "message1 Construct" << std::endl;
    }

    Message1(int a)
    {
        std::cout << "message1" << std::endl;
    }

    ~Message1()
    {

    }

    void foo()
    {
        std::cout << "message1 foo" << std::endl;
    }
};



REGISTER_MESSAGE(Message1,"message1");
