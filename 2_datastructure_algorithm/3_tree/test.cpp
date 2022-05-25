#include <iostream>

using namespace std;

int find_int_arg(int argc, char *argv[], char *arg)
{
    for(int i = 0; i < argc; ++i)
    {
        if(!argv[i]) continue;
        if(0 == strcmp(argv[i], arg))
        {
            int res = atoi(argv[i+1]);
            return res;
        }
    }

    return 0;
}

int main()
{
    char *arg[] = {"1",(char*)"2",(char*)"3"};
    int x = find_int_arg(1,arg,1);
    cout << arg[1] << endl;
    return 0;
}
