//
// Created by likun on 5/28/23.
//

#include <iostream>

using namespace std;

class cola
{
};

class coca_cola : public cola
{
public:
    coca_cola(){cout<<"a coca_cola"<<endl;}
};

class pesi_cola : public cola
{
public:
    pesi_cola(){cout<<"a pesi_cola"<<endl;}
};

class bottle
{
};

class coca_bottle : public bottle
{
public:
    coca_bottle(){cout<<" a coca_bottle"<<endl;}
};

class pesi_bottle : public bottle
{
public:
    pesi_bottle(){cout<<"a pesi_bottle"<<endl;}
};

class box
{};

class coca_box:public box
{
public:
    coca_box(){cout<<" a coca_box"<<endl;}
};

class pesi_box:public box
{
public:
    pesi_box(){cout<<" a pesi_box"<<endl;}
};

class Factory
{
public:
    virtual cola* creator_cola() =0;
    virtual bottle* creator_bottle() =0;
    virtual box* creator_box() =0;
};

class coca_Factory : public Factory
{
public:
    coca_cola* creator_cola(){return new coca_cola;}
    coca_bottle* creator_bottle(){return new coca_bottle;}
    coca_box* creator_box() {return new coca_box;}
};

class pesi_Factory : public Factory
{
public:
    pesi_cola* creator_cola(){return new pesi_cola;}
    pesi_bottle* creator_bottle(){return new pesi_bottle;}
    pesi_box* creator_box() {return new pesi_box;}
};

int main(int argc, char** argv)
{
    coca_Factory coca_1;
    pesi_Factory pesi_1;
    cout<<"if there is coca Factory, there will have "
    <<coca_1.creator_cola()<<" and "<<coca_1.creator_bottle()
    <<" and "<<coca_1.creator_box()<<endl;
    cout<<"if there is pesi Factory, there will have "
        <<pesi_1.creator_cola()<<" and "<<pesi_1.creator_bottle()
        <<" and "<<pesi_1.creator_box()<<endl;

    return 0;
}





