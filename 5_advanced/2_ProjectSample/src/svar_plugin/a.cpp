#include "Svar.h"
#include "user_data.h"

#include <iostream>
#include <vector>


// C++ 内置变量的函数
double add(double a , double b){
    std::cout<<__FILE__<<std::endl;
    return a+b;
}


// 定义了一个用户定义变量的输入
int list(sv::Svar &a)
{
    std::vector<UserData> b = a.castAs<std::vector<UserData>>();
    std::cout << "[B] List contents: " << std::endl;
    for(auto i : b) {
        std::cout << __FILE__ << " " << i.id << ", name: " << i.name << std::endl;
    }
}


// 注册一个Svar模块
REGISTER_SVAR_MODULE(a){
    svar["add"] = add;              // 将每个函数加入到Svar模块
    svar["list"] = list;
}

EXPORT_SVAR_INSTANCE                // export 这个模块
