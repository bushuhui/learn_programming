#include <iostream>
#include <string>
#include <type_traits>

#include "factory.h"



int main(void)
{

    MessagePtr p = Factory::get().produce("message2");
    p->foo();
   return 0;
}
