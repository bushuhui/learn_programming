#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <GSLAM/core/Svar.h>

/**
 * basic_ios
 * istream,ostream-> iostream
 * ifstream,ofstream  stringstream
 */
class Point{
public:
    double x,y,z;
};

std::ostream& operator<<(std::ostream& os,const Point& p)
{
    os<<p.x<<" "<<p.y<<" "<<p.z;
    return os;
}

std::istream& operator>>(std::istream& is,Point& p)
{
    is>>p.x>>p.y>>p.z;
}

int testStream()
{
    std::cout<<"cout"<<std::endl;
    std::cerr<<"cerr"<<std::endl;
    int num;
    std::cin>>num;//istream
    std::cout<<"num:"<<num;

    std::ifstream ifs("in.txt");
    std::ofstream ofs("out.txt");
    if(!ifs.is_open())
        return -1;

    ifs>>num;
    ofs<<num;

    std::stringstream sst("");
    sst<<num;
    sst>>num;
    return 0;
}

class Person
{
public:
    Person(std::string name="admin",int age=0)
        : _name(name),_age(age){
        std::cerr<<"create Person"<<std::endl;
    }
    ~Person(){
      std::cerr<<"Object "<<_name<<" are leaving.";
    }

    virtual std::string introduction()const{
        std::stringstream sst;
        sst<<"name:"<<_name<<", age:"<<_age;
        return sst.str();
    }

    const std::string& name()const{return _name;}
    std::string& name(){return _name;}

    int         _age;
protected:
    std::string _name;
};

class SchoolInterface
{
public:
    SchoolInterface(std::string name="manager")
        :managerName(name){}
    virtual std::string getSchoolName()const{return "none";}

    std::string managerName;
    int         fdalfda;
};

class Student : public Person,public SchoolInterface{
public:
    Student(std::string name="admin",
            int age=0,std::string school="world");

    Student(Person person,std::string school="world");

    std::string school(){return _school;}

    virtual std::string introduction()const{
        std::stringstream sst;
        sst<<Person::introduction()
          <<", school:"<<_school;
        return sst.str();
    }

    virtual std::string getSchoolName()const{return _school;}

    std::string _school;
};

Student::Student(std::string name, int age, std::string school)
    : Person(name,age),_school(school){

}

Student::Student(Person person,std::string school)
    : Person(person),_school(school)
{

}

int main(int argc,char** argv){
    Person  person("zhaoyong",12);
    Student student("zhaoyong",12,"npu");

    Person* p1=&person;
    Person* p2=&student;

    SchoolInterface* interface=dynamic_cast<SchoolInterface*>(&student);
    Student* stu=dynamic_cast<Student*>(p1);

    auto school=stu?stu->school():std::string("NoneSchool");
    std::cerr<<p1->introduction()<<std::endl;
    std::cerr<<p2->introduction()<<std::endl;
    std::cerr<<school<<std::endl;
    std::cerr<<interface->managerName<<std::endl;

    Person* p3(new Person());
    Person* p4(new Student());
    std::cerr<<p3->introduction()<<std::endl;
    std::cerr<<p4->introduction()<<std::endl;

    double* p=new double(1);
    double* ptr=(double*)malloc(sizeof(double));
    delete  p;
    delete  ptr;

    int n;
    std::cin>>n;
    double* pmulti=(double*)malloc(n*sizeof(double));
    double* ptrmulti=new double[n];
    free(pmulti);
    delete[] ptrmulti;

    Person* persons=new Person[2];
    delete[] persons;
    std::cerr<<"released";

    std::shared_ptr<Person> personPtr(new Student("newstudent"));


    Person &ref=person,&ref1=student;
    ref._age=100;
    ref1._age=120;
    std::cerr<<person._age<<","<<student._age;

    std::cerr<<ref.introduction();
    std::cerr<<ref1.introduction();

    std::cerr<<Point();

    {
        const Person person;
        std::string name=person.name();
    }

    return 0;
}
