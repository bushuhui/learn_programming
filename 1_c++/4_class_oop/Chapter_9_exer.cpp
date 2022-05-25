//10/23
//第九章 继承与派生 练习题 p225

#include <iostream>
#include <string>

using namespace std;

// 1.点、圆、圆柱及其相关参数

/////////////////////////////////////////////////////////////////////
class Point
{
public:
    void set(double xx, double yy);
    void display();
    Point(double xx, double yy);
    Point();
    ~Point();
protected:
    double x, y;
};

Point::Point(double xx, double yy)
{
    x = xx;
    y = yy;
}

Point::Point()
{}

Point::~Point()
{
    cout << "Point destructor is used." << endl;
}

void Point::set(double xx, double yy)
{
    x = xx;
    y = yy;
}

void Point::display()
{
    cout << "Point coordinate: (" << x << ',' << y << ')' << endl;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

class Circle:public Point
{
public:
    void   set(double xx, double yy, double rr);
    void   display();
    double area();
    Circle(double xx, double yy, double rr);
    Circle();
    ~Circle();
protected:
    double radius;
    static const double PI;
};

const double Circle::PI = 3.1415926;

Circle::Circle(double xx, double yy, double rr):Point(xx, yy)
{
    radius = rr;
}

Circle::Circle():Point()
{
}

Circle::~Circle()
{
    cout << "Circle destructor is used." <<endl;
}

void Circle::set(double xx, double yy, double rr)
{
    Point::set(xx, yy);
    radius = rr;
}

void Circle::display()
{
    Point::display();
    cout << "Circle radius: " << radius << endl;
    cout << "Circle area: " << area() << endl;
}

double Circle::area()
{
    return radius*radius*PI;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

class Cylinder:public Circle
{
public:
    void   set(double xx, double yy, double rr, double h);
    void   display();
    double surface_area();
    double volume();
    Cylinder(double xx, double yy,double rr, double h);
    Cylinder();
    ~Cylinder();
private:
    double height;
};

Cylinder::Cylinder(double xx, double yy, double rr, double h):Circle(xx, yy, rr)
{
    height = h;
}

Cylinder::Cylinder():Circle()
{}

Cylinder::~Cylinder()
{
    cout << "Cylinder destructor is used." << endl;
}

void Cylinder::set(double xx, double yy, double rr, double h)
{
    Circle::set(xx, yy, rr);
    height = h;
}

void Cylinder::display()
{
    Circle::display();
    cout << "Cylinder height: " << height << endl;
    cout << "Cylinder surface area: " << surface_area() << endl;
    cout << "Cylinder volume: " << volume() << endl;
}

double Cylinder::surface_area()
{
    return 2*Circle::area() + 2*PI*radius*height;
}

double Cylinder::volume()
{
    return Circle::area() * height;
}
/////////////////////////////////////////////////////////////////////

void q1_cylinder()
{
    Circle c1(0, 0, 30);
    Circle c2;
    c1.display();
    c2.set(-5, -5, 25);
    c2.display();
    cout << "-------" << endl;

    Cylinder cy1(0, 0, 30, 15);
    Cylinder cy2;
    cy2.set(-5, -5, 25, 70);
    cy1.display();
    cy2.display();
}

// 2.车。多继承

/////////////////////////////////////////////////////////////////////
class Automobile
{
public:
    void input();
    void display();
    Automobile(string bands, string colors, int weights, int powers);
    Automobile();
protected:
    string band;
    string color;
    int    weight;
    int    power;
};

Automobile::Automobile(string bands, string colors, int weights, int powers)
{
    band = bands;
    color = colors;
    weight = weights;
    power = powers;
}

Automobile::Automobile()
{
}

void Automobile::input()
{
    cout << "Enter band: ";
    cin >> band;
    cout << "Enter color:";
    cin >> color;
    cout << "Enter weight:";
    cin >> weight;
    cout << "Enter powerhorse: ";
    cin >> power;
}

void Automobile::display()
{
    cout << "Band: " <<  band << endl;
    cout << "Color: " << color << endl;
    cout << "Weight: " << weight << endl;
    cout << "Powerhorse: " << power << endl;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

class Car:virtual public Automobile
{
public:
    void input();
    void display();
    Car(string bands, string colors, int weights, int powers, int seats);
    Car();
protected:
    int seat;
};

Car::Car(string bands, string colors, int weights, int powers, int seats)\
    :Automobile(bands, colors, weights, powers)
{
    seat = seats;
}

Car::Car():Automobile()
{}

void Car::input()
{
    Automobile::input();
    cout << "Enter seat number:";
    cin >> seat;
}

void Car::display()
{
    Automobile::display();
    cout << "Seat number: " << seat << endl;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

class Wagon:virtual public Automobile
{
public:
    void input();
    void display();
    Wagon(string bands, string colors, int weights, int powers, int loads);
    Wagon();
protected:
    int load;
};

Wagon::Wagon(string bands, string colors, int weights, int powers, int loads)\
    :Automobile(bands, colors, weights, powers)
{
    load = loads;
}

Wagon::Wagon():Automobile()
{
}

void Wagon::input()
{
    Automobile::input();
    cout << "Enter load weight: ";
    cin >> load;
}

void Wagon::display()
{
    Automobile::display();
    cout << "Load weight: " << load << endl;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

class StationWagon:public Car, public Wagon
{
public:
    void input();
    void display();
    StationWagon(string bands, string colors, int weights, int powers, int seats, int loads);
    StationWagon();
};

StationWagon::StationWagon(string bands, string colors, int weights, \
                           int powers, int seats, int loads)\
    :Car(bands, colors, weights, powers, seats),\
      Wagon(bands, colors, weights, powers, loads),\
      Automobile(bands, colors, weights, powers)
{}

StationWagon::StationWagon():Car(),Wagon(),Automobile()
{}

void StationWagon::input()
{
    Car::input();
    cout << "Enter load weight: ";
    cin >> load;
}

void StationWagon::display()
{
    Car::display();
    cout << "Load weight: " << load << endl;
}

void q2_car()
{
    StationWagon sw1("0000", "Black", 4, 4000, 10, 2);
    StationWagon sw2;
    sw2.input();
    sw1.display();
    sw2.display();
}
/////////////////////////////////////////////////////////////////////


// 3,4 与1,2相似，不再重复


int main()
{
    //q1_cylinder();
    q2_car();

    return 0;
}






