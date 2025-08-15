#include <stdio.h>
#include <algorithm>

using namespace std;

struct rectangle{
	int number;
	int length;
	int wide;
} rec[1005];
 
int cmp(rectangle a,rectangle b)
{
	if(a.number!=b.number)
	{
		return a.number < b.number;
	}else if(a.length!=b.length){
		return a.length < b.length;
	}else if(a.wide!=b.wide){
		return a.wide<b.wide; 
	}
}

bool isEquals(rectangle x,rectangle y)
{
	if(x.number==y.number&&x.length==y.length&&x.wide==y.wide)
	{
		return true;
	}else{
		return false;
	}
}

int main()
{
	int n;
	scanf("%d",&n);
	while(n--)
	{
		int m;
		scanf("%d",&m);
		for(int i = 0; i < m; i++)
		{
			scanf("%d%d%d",&rec[i].number,&rec[i].length,&rec[i].wide);
			int t;
			if(rec[i].length<rec[i].wide)
			{
				t = rec[i].length;
				rec[i].length=rec[i].wide;
				rec[i].wide = t;
			}
		}
		sort(rec,rec+m,cmp);
		for(int i = 0; i < m; i++)
		{
			if(!isEquals(rec[i],rec[i+1]))
			{
				printf("%d %d %d\n",rec[i].number,rec[i].length,rec[i].wide);
			}
		}
		
	}
	return 0;
}

