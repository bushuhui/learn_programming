#include <stdio.h>

#include <cstdio>  
#include <cstring>  
#include <algorithm>  

using namespace std; 
 
int test_1()  
{  
    int n;  
    scanf("%d",&n);  
    while(n--)  
    {  
        char a[10];  
        scanf("%s",a);  
        int l=strlen(a);  
        int k=1;  
        for(;a[k]=='0';k++); 
        for(int i=k;i<l-1;i++)  
           	printf("%d",a[i]-'0');  
        printf("%d\n",a[l-1]-'0');  
    }  
    return 0;  
}  

int test_2()
{
	int num, M;
	scanf("%d",&num);
	while(num--){
		scanf("%d",&M);
		int i = 10;
		while(M/i >= 10){
			i = i * 10;
		}
		printf("%d\n",M%i);
	}
}

int main(int argc, char *argv[])
{
    test_2();

    return 0;
}

