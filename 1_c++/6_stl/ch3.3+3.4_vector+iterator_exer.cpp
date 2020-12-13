//12/13
//C++ Primer 3.3 标准库类型vector 练习题
//C++ Primer 3.4 迭代器 练习题

#include <iostream>
#include <vector>

using namespace std;

//3.14-3.15

void q3_14_readInVector()
{
    vector<int> vi;
    vector<string> vs;
    int i;
    string s;
    int a = 0;
    while(cin >> i)
    {
        if(i == 0)
        {
            break;
        }
        vi.push_back(i);
    }
    for(auto j : vi)
    {
        cout << j << " ";
    }
    cout << endl;

    while(cin >> s)
    {
        vs.push_back(s);
        a++;
        if(a == 5)
        {
            break;
        }
    }

    for(auto k : vs)
    {
        cout << k << " ";
    }
    cout << endl;
}

//3.20

void q3_20_sum2Number()
{
    vector<int> v;
    vector<int>::iterator vi;
    int i;
    while((cin >> i) && i != 0)
    {
        v.push_back(i);
    }
    if(v.size() % 2 == 1)
    {
        v.pop_back();
    }
    for(vi = v.begin(); vi != v.end(); vi += 2)
    {
        cout << *vi + *(vi+1) << " ";
    }
    cout << endl;

    vector<int>::iterator vie;
    vie = v.end()-1;
    for(vi = v.begin(); vi != v.begin() + v.size()/2; vi++)
    {
        cout << *vi + *vie << " ";
        vie--;
    }
    cout << endl;
}

int main()
{
    //q3_14_readInVector();
    q3_20_sum2Number();

    return 0;
}
