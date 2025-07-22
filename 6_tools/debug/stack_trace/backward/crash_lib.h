#ifndef CRASH_LIB_H
#define CRASH_LIB_H

extern "C" {
    // 空指针访问崩溃
    void crash_function_null_pointer();
    
    // 缓冲区溢出崩溃
    void crash_function_buffer_overflow();
    
    // 栈溢出崩溃
    void crash_function_stack_overflow();
    
    // 野指针访问崩溃
    void crash_function_wild_pointer();
    
    // 嵌套函数调用中的崩溃
    void nested_crash_call();
    void another_nested_call();
    void final_crash_call();
}

#endif // CRASH_LIB_H