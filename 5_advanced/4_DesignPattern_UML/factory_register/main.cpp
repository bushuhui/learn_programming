#include <iostream>
#include <string>
#include <type_traits>
#include "factory.h"



int main(void)
{

    MessagePtr p = factory::get().produce("message2");
    p->foo();
   return 0;
}


//#include <iostream>
//#include <string>//using namespace std;

//class programmer
//{
//    string name;
//    string sex;
//    int age;
//    string vocation;//职业
//    double height;
//public:
//    programmer(string name, string sex, int age, string vocation, double height)
//    :name(name), sex(sex), age(age), vocation(vocation), height(height)
//    {
//        cout << "call programmer" << endl;
//    }

//    void print()
//    {
//        cout << "name:" << name << endl;
//        cout << "sex:" << sex << endl;
//        cout << "age:" << age << endl;
//        cout << "vocation:" << vocation << endl;
//        cout << "height:" << height << endl;

//    }
//};

//template<typename T>
//class xprintf
//{
//    T * t;
//public:
//    xprintf()
//    :t(nullptr)
//    {}

//    template<typename ... Args>
//    void alloc(Args ... args)
//    {
//        t = new T(args...);
//    }

//    void print()
//    {
//        t->print();
//    }

//    void afree()
//    {
//        if ( t != nullptr )
//        {
//            delete t;
//            t = nullptr;
//        }
//    }
//};

//int main()
//{
//    xprintf<programmer> xp;
//    xp.alloc("小明", "男", 35, "程序员", 169.5);
//    xp.print();
//    xp.afree();
//    return 0;
//}
