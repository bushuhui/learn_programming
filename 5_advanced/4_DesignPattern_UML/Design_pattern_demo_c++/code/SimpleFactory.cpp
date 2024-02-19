#include <iostream>

using namespace std;

enum cola_type{Coca, Pesi};

class cola
{

};

class coca_cola : public cola{
public:
    coca_cola(){cout<<"this is coca_cola class"<<endl;}
};

class pesi_cola : public cola{
public:
    pesi_cola(){cout<<"this is pesi_cola class"<<endl;}
};

class cola_factory
{
public:
    cola* creator_cola_with_type(cola_type type)
    {
        switch(type){
            case Coca:
                return new coca_cola;
                break;
            case Pesi:
                return new pesi_cola;
                break;
            default:
                return nullptr;
                break;
        }
    }
};

int main(int argc, char** argv)
{
    cola_factory cf;
    cola_type c1(Coca), c2(Pesi);
    cola *coca, *pesi;
    coca = cf.creator_cola_with_type(c1);
    pesi = cf.creator_cola_with_type(c2);
    return 0;
}