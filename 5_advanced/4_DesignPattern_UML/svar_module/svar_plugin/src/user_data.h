#pragma once

#include <string>

struct UserData
{
    std::string name;
    int         id;

public:
    UserData(char *_n, int _i) : name(_n), id(_i) {}
};
