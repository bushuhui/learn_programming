//11/27
// 算法与数据结构，第一章，入门

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

//malloc 与 free

void mal_free()
{
    int *p;
    p = (int *)malloc(sizeof(int));
    if (p==NULL)
    {
    	cerr << "Memory allocation error." << endl;
        exit(1);
    }
    *p = 5;
    cout << *p;
    
    free(p);    //释放p的内存
    p = NULL;   //p指针赋为空
}

int main()
{
    mal_free();

    return 0;
}

