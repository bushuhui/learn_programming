//10/21
//第八章 静态

#include <iostream>
#include <string>

using namespace std;

//静态数据成员及静态函数

class Rectangle
{
public:
    void        info_display();
    int         area();
    int         perimeter();
    int         counting();
    static int  total(); //静态函数
    
    // FIXME: 建议参数用引用，例如"Rectangle &p1"
    friend int  area_diff(Rectangle &p1, Rectangle &p2);    //普通友元函数声明
    Rectangle(int l, int w);
private:
    int        length, width;
    static int count;   //静态数据
};

int Rectangle::count = 0;   //静态数据初始化

Rectangle::Rectangle(int l, int w)
{
    length = l;
    width = w;
}

void Rectangle::info_display()
{
    cout << "This rectangle is " << length << " long and " << width << " wide, with " \
         << " area of " << area() << " and perimeter of " << perimeter() << endl;
}

int Rectangle::area()
{
    int s;
    s = length * width;

    return s;
}

int Rectangle::perimeter()
{
    int p;
    p = 2*(length + width);

    return p;
}

int Rectangle::total()
{
    return count;
}

int Rectangle::counting()
{
    count++;

    return count;
}

int area_diff(Rectangle &p1, Rectangle &p2)   //友元函数定义
{
    int diff;
    diff = p1.length*p1.width - p2.length*p2.width;
    cout << "Area difference of p1 and p2 is: " << diff << endl;

    return diff;
}

void test_rectangle()
{
    Rectangle p1(3, 5);
    p1.counting();
    p1.area();
    p1.perimeter();
    p1.info_display();
    Rectangle p2(7,3);
    p2.counting();
    p2.info_display();
    cout << Rectangle::total() << endl;
    area_diff(p1, p2);
}

//类成员的友元函数  //friend int Rectangle::visit();
//友元类   //friend class Rectangle;

int main()
{
    test_rectangle();

    return 0;
}
