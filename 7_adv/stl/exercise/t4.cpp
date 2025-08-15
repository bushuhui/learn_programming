#include <stdio.h>  
#include <map>  
#include <algorithm>  
using namespace std;  

int main()  
{  
    map<int, int>a;   
    int n, m, i, max, key, x;  
    scanf("%d", &n);  
    while(n--)  
    {  
        max = key = 0;  
        a.clear();  
        scanf("%d", &m);  
        for(i = 0 ; i < m ; i++)  
        {  
            scanf("%d", &x);  
            a[x]++;  
            if(a[x] > key)  
            {  
                key = a[x];  
                max = x;  
            }  
        }  
        printf("%d %d\n", max, key);  
    }  
    return 0;  
}
