#include <iostream>

using namespace std;

class shape{
public:
    virtual void draw() = 0;
};

class rectangle : public shape
{
public:
    void draw(){cout<<"print rectangle "<<endl;}
};

class square : public shape
{
public:
    void draw(){cout<<"print square "<<endl;}
};

class circle : public shape
{
public:
    void draw(){cout<<"print circle "<<endl;}
};

class shape_manager{
public:
    shape_manager()
    {
        m_rectangle = new rectangle();
        m_circle = new circle();
        m_square = new square();
    }
    void draw(){
        m_rectangle->draw();
        m_square->draw();
        m_circle->draw();
    }

private:
    rectangle* m_rectangle;
    square* m_square;
    circle* m_circle;
};

int main()
{
    shape_manager drawer;
    drawer.draw();
    return 0;
}



