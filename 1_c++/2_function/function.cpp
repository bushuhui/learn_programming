#include <stdio.h>

int print_message(const char *msg)
{
    printf("message: %s\n", msg);
}


int main(int argc, char *argv[])
{
    char buf[256];

    for(int i=0; i<10; i++) 
    {
        sprintf(buf, "[%4d]", i);
        print_message(buf)
    }

    return 0;
}

