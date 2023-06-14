//
// Created by likun on 5/28/23.
//

#include <iostream>

using namespace std;

class Cola
{
};

class coca_cola : public Cola
{
};

class pesi_cola: public Cola
{};

class Factory
{
public:
    virtual Cola* product()=0;
};

class coca_cola_Factory : public Factory
{
public:
    coca_cola_Factory(){cout<<"the coca cola Factory"<<endl;}
    Cola* product()
    {
        cout<<" product a new coca cola !"<<endl;
        return new coca_cola;
    }
};

class pesi_cola_Factory: public Factory
{
public:
    pesi_cola_Factory(){cout<<"the pesi cola Factory"<<endl;}
    Cola* product()
    {
        cout<<" product a new pesi cola !"<<endl;
        return new pesi_cola;
    }
};

int main(int argc, char **argv)
{
    Cola *cola1, *cola2;
    Factory *fac1 = new coca_cola_Factory;
    Factory *fac2 = new pesi_cola_Factory;
    cola1 = fac1->product();
    cola2 = fac2->product();
    return 0;
}
