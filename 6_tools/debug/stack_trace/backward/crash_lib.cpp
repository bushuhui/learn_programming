#include "crash_lib.h"
#include <cstring>
#include <iostream>

void crash_function_null_pointer() {
    std::cout << "即将访问空指针..." << std::endl;
    int* ptr = nullptr;
    *ptr = 42;  // 这将导致段错误
}

void crash_function_buffer_overflow() {
    std::cout << "即将访问越界内存..." << std::endl;
    char buffer[10];
    strcpy(buffer, "这是一个很长的字符串，会导致缓冲区溢出");
}

void crash_function_stack_overflow() {
    std::cout << "即将发生栈溢出..." << std::endl;
    crash_function_stack_overflow();  // 无限递归
}

void crash_function_wild_pointer() {
    std::cout << "即将访问野指针..." << std::endl;
    int* ptr = (int*)0xDEADBEEF;
    *ptr = 123;  // 访问无效内存地址
}

void nested_crash_call() {
    another_nested_call();
}

void another_nested_call() {
    final_crash_call();
}

void final_crash_call() {
    std::cout << "在深层嵌套函数中触发崩溃..." << std::endl;
    int* ptr = nullptr;
    *ptr = 99;  // 段错误
}