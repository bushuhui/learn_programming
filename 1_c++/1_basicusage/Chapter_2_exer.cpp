//10/11
//《C++程序设计》第三版，齐建玲等 练习题 p49

#include <iostream>
#include <cmath>

using namespace std;

// 1.求100内自然数奇数和
int odd()
{
    int i = 1;
    int sum = 0;
    for (i; i <= 100; i++)
    {
        if (i%2 == 1)
        {
            sum += i;
        }
    }
    cout << sum << endl;

    return sum;
}

// 2.求100内被13整除的最大整数
int div13()
{
    int i = 1;
    int ans;
    int choice[100];
    int pos = 0;
    for (i; i <= 100; i++)
    {

        if (i%13 == 0)
        {
            choice[pos] = i;
            pos++;
        }
    }
    ans = choice[pos - 1];
    cout << ans << endl;

    return ans;
}

// 3.根据输入的x，输出 y=f(x)的值
int fx()
{
    int x, ans;
    cout << "Please input x:";
    cin >> x;
    if (x < 1)
    {
        ans = x;
    }
    else if (x > 10)
    {
        ans = x - 5;
    }
    else if ((x > 1) && (x < 10))
    {
        ans = x + 5;
    }
    cout << ans << endl;

    return ans;
}

// 4.三数排序
int order3()
{
    //3数
    int a, b, c, tran;
    cout << "Please input 3 numbers:";
    cin >> a >> b >> c;
    a > b ?: (tran = a, a = b, b = tran);
    a > c ?: (tran = a, a = c, c = tran);
    b > c ?: (tran = b, b = c, c = tran);
    cout << c << endl;
    cout << a << ">"<< b << ">" << c;

    return 0;
}

// 5.冒泡排序
void bubble_sort()
{
    int arr[10000];
    int n;
    cout << "Please input numbers, enter 0 to end inputing:";
    for (n = 0;;n++)
    {
        cin >> arr[n];
        if (arr[n]==0)
        {
            break;
        }
    }
    for (int a = 0; a < n - 1; a++)
    {
        for (int b = a + 1; b <= n; b++)
        {
            int t;
            arr[a] > arr[b] ?: (t = arr[a], arr[a] = arr[b], arr[b] = t);
        }
    }
    for (int i = 0; i <= n;i++)
    {
        if (i < n)
        {
            cout << arr[i] << ">";
        }
        else if (i == n)
        {
            cout << arr[i] << endl;
        }
    }
}

// 5.输入数字，输出星期
void week()
{
    int wnum;
    cout << "Please input number of 1 to 7 for weekday:";
    cin >> wnum;
    switch (wnum)
    {
        case 1:
            cout << "Monday" << endl;
            break;
        case 2:
            cout << "Tuesday" << endl;
            break;
        case 3:
            cout << "Wednesday" << endl;
            break;
        case 4:
            cout << "Thursday" << endl;
            break;
        case 5:
            cout << "Friday" << endl;
            break;
        case 6:
            cout << "Saturday" << endl;
            break;
        case 7:
            cout << "Sunday" << endl;
            break;
    }
}

// 6.阶乘
int factr()
{
    int num, faco;
    faco = 1;
    cout << "Please input integer for factorial:";
    cin >> num;
    for (num; num > 0; num--)
    {
        faco *= num;
    }
    cout << faco << endl;
    return faco;
}

// 7.计算器
int cal()
{
    int a, b;
    double ans;
    char op;
    cout << "Please input 2 numbers:";
    cin >> a >> b;
    cout << "Please input operator:";   //未学会字符串处理，将运算符分开输入
    cin >> op;
    switch (op)
    {
        case '*':
            ans = a * b;
            break;
        case '-':
            ans = a - b;
            break;
        case '+':
            ans = a + b;
            break;
        case '/':
            ans = a / b;
    }
    cout << "Answer is: " << ans << endl;

    return ans;
}

// 8.打印图案
void printer()
{
    int c = 1;
    for (int a = 5; a > 0;a--)
    {

        for (int b = 1; b <= c; b++)
        {
            cout << '*';
        }
        cout << endl;
        c = c + 2;
    }
}

int main()
{
    odd();
    div13();
    //fx();
    //order3();
    //bubble_sort();
    //week();
    //factr();
    //cal();
    printer();

    return 0;
}

// FIXME:
//  1. 做的挺好的，继续努力！


