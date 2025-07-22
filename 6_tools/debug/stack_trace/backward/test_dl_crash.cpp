#define BACKWARD_HAS_BFD 1
#define BACKWARD_HAS_LIBUNWIND 1

#include "backward.hpp"
#include <iostream>
#include <dlfcn.h>
#include <signal.h>
#include <unistd.h>

// Signal handling 将在主函数中初始化

typedef void (*CrashFunction)();

void signal_handler(int signal) {
    std::cout << "\n=== 捕获到信号 " << signal << " ===\n" << std::endl;
    
    backward::StackTrace st;
    st.load_here(32);
    
    backward::Printer p;
    p.object = true;
    p.color_mode = backward::ColorMode::always;
    p.address = true;
    
    std::cout << "堆栈回溯信息：\n" << std::endl;
    p.print(st, stdout);
    
    exit(signal);
}

void setup_signal_handlers() {
    signal(SIGSEGV, signal_handler);
    signal(SIGABRT, signal_handler);
    signal(SIGFPE, signal_handler);
    signal(SIGILL, signal_handler);
    signal(SIGBUS, signal_handler);
}

int main() {
    std::cout << "=== 动态库加载和堆栈回溯测试程序 ===" << std::endl;
    
    // 初始化 backward 信号处理
    //backward::SignalHandling sh;
    
    // 设置信号处理器
    //setup_signal_handlers();
    
    // 动态加载库
    void* handle = dlopen("./libcrash.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "无法加载动态库: " << dlerror() << std::endl;
        return 1;
    }
    
    std::cout << "成功加载动态库 libcrash.so" << std::endl;
    
    // 显示可用的崩溃测试选项
    std::cout << "\n可用的崩溃测试选项：" << std::endl;
    std::cout << "1. 空指针访问" << std::endl;
    std::cout << "2. 缓冲区溢出" << std::endl;
    std::cout << "3. 栈溢出" << std::endl;
    std::cout << "4. 野指针访问" << std::endl;
    std::cout << "5. 嵌套函数调用崩溃" << std::endl;
    
    int choice;
    std::cout << "\n请选择测试类型 (1-5): ";
    std::cin >> choice;
    
    CrashFunction crash_func = nullptr;
    
    switch (choice) {
        case 1: {
            crash_func = (CrashFunction)dlsym(handle, "crash_function_null_pointer");
            std::cout << "选择了：空指针访问测试" << std::endl;
            break;
        }
        case 2: {
            crash_func = (CrashFunction)dlsym(handle, "crash_function_buffer_overflow");
            std::cout << "选择了：缓冲区溢出测试" << std::endl;
            break;
        }
        case 3: {
            crash_func = (CrashFunction)dlsym(handle, "crash_function_stack_overflow");
            std::cout << "选择了：栈溢出测试" << std::endl;
            break;
        }
        case 4: {
            crash_func = (CrashFunction)dlsym(handle, "crash_function_wild_pointer");
            std::cout << "选择了：野指针访问测试" << std::endl;
            break;
        }
        case 5: {
            crash_func = (CrashFunction)dlsym(handle, "nested_crash_call");
            std::cout << "选择了：嵌套函数调用崩溃测试" << std::endl;
            break;
        }
        default:
            std::cout << "无效选择，使用默认的空指针访问测试" << std::endl;
            crash_func = (CrashFunction)dlsym(handle, "crash_function_null_pointer");
            break;
    }
    
    if (!crash_func) {
        std::cerr << "无法找到函数符号: " << dlerror() << std::endl;
        dlclose(handle);
        return 1;
    }
    
    std::cout << "\n开始执行崩溃测试..." << std::endl;
    std::cout << "3秒后开始..." << std::endl;
    sleep(3);
    
    // 调用会导致崩溃的函数
    crash_func();
    
    // 这里永远不会被执行到
    dlclose(handle);
    return 0;
}