#include "Svar.h"
#include <iostream>

using namespace sv;

void c_func_demo(Svar arg){
    std::cout<<"Calling a c_func with arg "<<arg<<std::endl;
}

class Person{
public:
    Person(int age,std::string name)
        : _age(age),_name(name){
        all_person()[name]=_age;
    }

    virtual std::string intro()const{
        return Svar({{"Person",{_age,_name}}}).dump_json();
    }

    int age()const{return _age;}

    static Svar& all_person(){
        static Svar all;
        return all;
    }

    int _age;
    std::string _name;
};

int main(int argc, char *argv[])
{
    svar["func"]=c_func_demo;
    std::cout<<svar["func"]("123")<<std::endl;

    // define the class to svar
    Class<Person>("Person","The base class")
            .construct<int,std::string>()
            .def("intro",&Person::intro)
            .def_static("all",&Person::all_person)
            .def("age",&Person::age)
            .def_readonly("name",&Person::_name,"The name of a person");

    // use the class with svar
    Svar Person=svar["Person"];

    std::cout<<Person.as<SvarClass>();


    Svar father=Person(40,"father");
    Svar mother=Person(39,"mother");


    std::cout<<"all:"<<Person.call("all")<<std::endl;
    std::cout<<father.call("intro").as<std::string>()<<std::endl;
    std::cout<<mother.call("age")<<std::endl;

}
