#include <stdio.h> 

#define MAX_LEVEL 4
#define NEW_GCC

#ifdef NEW_GCC
    #define OFFSET 4
#else
    #define OFFSET 0
#endif/*NEW_GCC*/ 

int backtrace(void** buffer, int size)
{
    int     n = 0xfefefefe;
    int*    p = &n;
    int     i = 0; 

    int ebp = p[1 + OFFSET];
    int eip = p[2 + OFFSET]; 

    for(i = 0; i < size; i++)
    {
        buffer[i] = (void*)eip;
        p = (int*)ebp;
        ebp = p[0];
        eip = p[1];
    } 

    return size;
} 



int backtrace_m(void **buffer, int size)
{
    int i = 0;

    unsigned int _ebp = 0;
    unsigned int _eip = 0;

    __asm__ __volatile__(" \
                         movl %%ebp, %0"
                         :"=g" (_ebp)
                         :
                         :"memory"
                         );

    for(i = 0; i < size; i++)
    {
        _eip = (unsigned int)((unsigned int*)_ebp + 1);
        _eip = *(unsigned int*)_eip;
        _ebp = *(unsigned int*)_ebp;
        buffer[i] = (void*)_eip;
    }

    return size;
}


static void test2()
{
    int i = 0;
    void* buffer[MAX_LEVEL] = {0}; 

    backtrace_m(buffer, MAX_LEVEL);

    for(i = 0; i < MAX_LEVEL; i++)
    {
        printf("called by %p/n",    buffer[i]);
    } 

    return;
} 

static void test1()
{
    int a=0x11111111;
    int b=0x11111112; 

    test2();
    a = b; 

    return;
} 

static void test()
{
    int a=0x10000000;
    int b=0x10000002; 

    test1();
    a = b; 

    return;
} 

int main(int argc, char* argv[])
{
    test(); 

    return 0;
}

