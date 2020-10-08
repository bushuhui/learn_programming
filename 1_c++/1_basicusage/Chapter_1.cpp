#include <iostream>
using namespace std;
int test_enum()
{
    enum color { red, green=7, gold, violet } c;
    c = gold;
    cout << c;
    return 0;
}

int main()
{
    test_enum();
}