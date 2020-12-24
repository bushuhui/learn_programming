//12/24
//数据结构 第六章 练习题 字符串、数组、矩阵

#include <iostream>
#include <string>

using namespace std;

//数组

//1.分糖果
//题述：有n个小朋友围坐成一圈。老师给每个小朋友随机发偶数个糖果，然后进行下面的游戏：
//每个小朋友都把自己的糖果分一半给左手边的孩子。
//一轮分糖后，拥有奇数颗糖的孩子由老师补给1个糖果，从而变成偶数。
//反复进行这个游戏，直到所有小朋友的糖果数都相同为止。
//你的任务是预测在已知的初始糖果情形下，老师一共需要补发多少个糖果。

//输入：程序首先读入一个整数N(2< N< 100)，表示小朋友的人数。
//接着是一行用空格分开的N个偶数（每个偶数不大于1000，不小于2）

//输出：要求程序输出一个整数，表示老师需要补发的糖果数。

//思路：可以套多个循环，一步一步做。或者在一个循环内实现，对一个小朋友而言，只有减半、添糖、补糖三个操作，完成之后就可以作为判断是否结束的依据
//因为是一个圆，故头尾需要单独定义

int q1_candy()
{
    int t_candy = 0, end = 1, len;
    cout << "enter kid number:";
    cin >> len;
    if(len<=2 || len >=100)
    {
        cout << "kid number error" << endl;
    }
    int kid[len];
    cout << "enter even candy numbers:" << endl;
    for(int i = 0; i < len; i++)
    {
        cin >> kid[i];
    }
    int f, b;
    while(end != 0)
    {
        end = 0;
        for(int j = 0; j < len; j++)
        {
            if(j == 0)
            {
                kid[j] /= 2;
                f = kid[j];
            }
            else if(j == len-1)
            {
                kid[j] /= 2;
                kid[0] += kid[j];
                kid[j] += f;
                if(kid[0]%2)
                {
                    kid[0]++;
                    t_candy++;
                }
                if(kid[j]%2)
                {
                    kid[j]++;
                    t_candy++;
                }
                if(kid[0] != kid[j])
                {
                    end++;
                }
                if(kid[0] != kid[1])
                {
                    end++;
                }
            }
            else
            {
                kid[j] /= 2;
                b = kid[j];
                kid[j] += f;
                if(kid[j]%2)
                {
                    kid[j]++;
                    t_candy++;
                }
                if(j>1 && kid[j-1] != kid[j])
                {
                    end++;
                }
                f = b;
            }
        }
    }

    for(int k = 0; k < len; k++)
    {
        cout << kid[k] << ' ';
    }
    cout << endl;

    return t_candy;
}

//2.蚂蚁感冒
//题述：长100厘米的细长直杆子上有n只蚂蚁。它们的头有的朝左，有的朝右。
//每只蚂蚁都只能沿着杆子向前爬，速度是1厘米/秒。
//当两只蚂蚁碰面时，它们会同时掉头往相反的方向爬行。
//这些蚂蚁中，有1只蚂蚁感冒了。并且在和其它蚂蚁碰面时，会把感冒传染给碰到的蚂蚁。
//请你计算，当所有蚂蚁都爬离杆子时，有多少只蚂蚁患上了感冒。

//输入：第一行输入一个整数n  (1  <   n  <   50),  表示蚂蚁的总数。
//接着的一行是n个用空格分开的整数  Xi  (-100  <   Xi  <   100),  Xi的绝对值，表示蚂蚁离开杆子左边端点的距离。
//正值表示头朝右，负值表示头朝左，数据中不会出现0值，也不会出现两只蚂蚁占用同一位置。
//其中，第一个数据代表的蚂蚁感冒了。

//输出：要求输出1个整数，表示最后感冒蚂蚁的数目。

//理解：所有朝向感冒蚂蚁的蚂蚁必定会导致一个蚂蚁感冒

int q2_antfever()
{
    int fever = 1, num;
    cout << "Enter ant number:";
    cin >> num;
    cout << "Enter ant position and direction:" << endl;
    int ant[num],feverant;
    for(int i = 0; i < num; i++)
    {
        cin >> ant[i];
    }

    feverant = abs(ant[0]);
    for(int i = 1; i < num; i++)
    {
        if(abs(ant[i]) < feverant && ant[i] > 0)
        {
            fever++;
        }
        else if(abs(ant[i]) > feverant && ant[i] < 0)
        {
            fever++;
        }
    }

    return fever;
}

//3.计算器
//题述：计算器显示器中将数字A变为数字B需要经过多少次变换？
//注意：现在将其中每段小二极管的开和关都定义为一次变换。例如数字1变为2是5次操作。
//【数据范围】
//L< =100

//输入：第一行为一个正整数L，表示数码的长度。
//接下来两行是两个长度为L的数字A和B，表示要把数字A变成数字B（数字可以以0开头）。

//输出：一行一个整数，表示这些小二极管一共要变换多少次。

//思路：将计算器数字映射为2进制码，亮管为1,暗管为0。
//对两个同位的数而言，其转换操作次数即为其对应数位上2进制码的异或运算所得为1的个数的和

char enumeration(char c)//枚举出每个数字的表示形式
{
    switch (c)
    {
    case '0':return 63;        //0111111
    case '1':return 6;        //0000110
    case '2':return 91;        //1011011
    case '3':return 79;        //1001111
    case '4':return 102;    //1100110
    case '5':return 109;    //1101101
    case '6':return 125;    //1111101
    case '7':return 7;        //0000111
    case '8':return 127;    //1111111
    case '9':return 111;    //1101111
    }
}

int judge(char c)//判断两个数异或所得的数的位为1的个数
{
    int count = 0;
    for (int i = 0; i < 7; ++i)
    {
        if (c&(1 << i))
            count++;
    }
    return count;
}

int q3_calculatorDisplay()
{
    int len, count = 0;
    cout << "Enter number length:";
    cin >> len;
    char a[len], b[len];
    cout << "Enter numer to be changed:";
    for (int i = 0; i < len; ++i)
    {
        cin >> a[i];
    }
    cout << "Enter number changing to:";
    for (int i = 0; i < len; ++i)
    {
        cin >> b[i];
    }

    for (int i = 0; i < len; ++i)
    {
        count += judge(enumeration(a[i]) ^ enumeration(b[i]));
    }

    return count;
}
int main()
{
    //cout << q1_candy() << endl;
    //cout << q2_antfever() << endl;
    cout << q3_calculatorDisplay() << endl;
    return 0;
}
