#include<cstdio>
#include<cstring>
#include<stack>
using namespace std;

//将输入的括号存在字符数组里面，定义一个栈s,遍历数组，如果数组元素与栈顶元素可匹配，出栈，否则入栈 
const int maxn = 10000 + 5;
char a[maxn];
int main(){
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",a);
		int len = strlen(a);
		stack<char>s;
		for(int i = 0; i < len; i++)
		{
			if(a[i] == ']'&&s.size()&&s.top()=='['){
				s.pop(); 
			}else if(a[i] == ')'&&s.size()&&s.top()=='('){
				s.pop();
			}else{
				s.push(a[i]);
			}
		}
		if(s.size())
		{
			printf("No\n"); 
		}else{
			printf("Yes\n");
		}
	}
	return 0;
}
