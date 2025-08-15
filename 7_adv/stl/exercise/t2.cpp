#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;

int main()
{
	int N;
	scanf("%d",&N);
	while(N--)
	{
		string a, b;
		cin>>a>>b;
		int count = 0; 
		int position = b.find(a,0);//find函数 返回jk在s中的下标位置 
		while(position!=string::npos)
		{
			count++;
			position = b.find(a,position+1);
		}
		printf("%d\n",count);
	}
	return 0;
}
