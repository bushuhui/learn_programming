#include <stdio.h>

int print_message(const char *msg)
{
    printf("message: %s\n", msg);
}

int pass_argument(int a, int b)
{
    printf("a = %d, b = %d\n", a, b);
    return 0;
}
    


int main(int argc, char *argv[])
{
    char buf[256];

    for(int i=0; i<10; i++) 
    {
        sprintf(buf, "[%4d]", i);
        print_message(buf);
    }

    pass_argument(10, 20);
    
    return 0;
}

