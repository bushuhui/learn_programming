//11/26
//第十三章 模板

#include <iostream>
#include <string>

using namespace std;

//函数模板

template <typename C>
C q1_pls(C x, C y)
{
    return x + y;
}

//类模板

template <class Number>
class Score
{
public:
    Score(Number x, Number y)
    {
        a = x;
        b = y;
    }
    Number total()
    {
        return a + b;
    }
    void display()
    {
        cout << "Sum is: " << total() << endl;
    }
private:
    Number a, b;
};

void q2_pls()
{
    Score<float> s(3, 5);
    s.display();
}

int main()
{
    cout << q1_pls(3, 5) << endl;
    q2_pls();
    return 0;
}