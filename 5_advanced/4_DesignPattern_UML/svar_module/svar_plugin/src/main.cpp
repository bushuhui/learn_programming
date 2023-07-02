#include "Svar.h"
#include <user_data.h>

#include <iostream>
#include <vector>
#include <string>


int main(int argc, char *argv[])
{
    // test simple function
    sv::Svar a = svar.import("a");  // import 插件 a
    sv::Svar b = svar.import("b");  // import 插件 a
    
    std::cout << a["add"](1,2) << std::endl;    // 调用基本函数 `add`
    std::cout << b["add"](3,4) << std::endl;    // 调用基本函数 `add`

    // test complex arguments (user defined data)
    std::vector<UserData> list1 = { UserData("Jack", 1), UserData("Tom", 2)};
    a["list"](list1);           // 调用复杂函数 `list`
    b["list"](list1);           // 调用复杂函数 `list`
    
    return 0;
}

