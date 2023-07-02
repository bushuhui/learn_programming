#pragma once

#include <string>

// 用户定义结构体
struct UserData
{
    std::string name;
    int         id;

public:
    UserData(char *_n, int _i) : name(_n), id(_i) {}
};
