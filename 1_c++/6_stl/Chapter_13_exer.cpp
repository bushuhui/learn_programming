//11/26
//第十三章 练习题 p300

#include <iostream>
#include <string>

using namespace std;

//1.求三数最大

template <class Number>
Number q1_max3(Number a, Number b, Number c)
{
    a > b ?: (a = b);
    a > c ?: (a = c);

    cout << "Max number is: " << a << endl;
    return a;
}

//2.交换值
template <class Number>
void q2_swap(Number a, Number b)
{
    Number c;
    c = a;
    a = b;
    b = c;
    cout << "Number after swap are: a:" << a << ", b: " << b << endl;
}

//3.数组模板

template <class Number>
class Array
{
public:
    void input()
    {
        cout << "Please input array numbers: ";
        for (int i = 0; i < 3; i++)
        {
            cin >> arr[i];
        }
    }
    void output()
    {
        cout << "Array numbers are: ";
        for (int j = 0; j < 3; j++)
        {
            cout << arr[j] << ", ";
        }
    }
    void sort()
    {
        for (int a = 0; a < 3; a++)
        {
            for (int b = a + 1; b <= 3; b++)
            {
                int t;
                arr[a] > arr[b] ?: (t = arr[a], arr[a] = arr[b], arr[b] = t);
            }
        }
    }
private:
    Number arr[3];
};

void q3_arrtemp()
{
    Array<float> arr1;
    arr1.input();
    arr1.output();
    arr1.sort();
    arr1.output();
}

int main()
{
    q1_max3(3, 8, 4);
    q2_swap(3, 5);
    q3_arrtemp();

    return 0;
}