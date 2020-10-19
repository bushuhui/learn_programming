//10/18
//第七章 类

#include <iostream>
#include <string>

using namespace std;

//类的定义,构造函数

class Computer
{
    public:
        void input_pc();
        void display();
        Computer();     //构造函数
        Computer(string producer, string gpu, string cpu, int ram); //重载
        Computer(const Computer& pc);   //复制构造函数
        ~Computer();   //析构函数

    private:
        string producer;
        string gpu;
        string cpu;
        int    ram;
};

Computer::Computer()    //无参
{
    producer = "None";
    gpu = "None";
    cpu = "None";
    ram = 0;
}

Computer::Computer(string producer, string gpu, string cpu, int ram): \
                   producer(producer), gpu(gpu),cpu(cpu),ram(ram)   //带参
{
}

Computer::Computer(const Computer& pc)
{
    producer = pc.producer;
    gpu = pc.gpu;
    cpu = pc.cpu;
    ram = pc.ram;
}

Computer::~Computer()
{
    cout << "Destructor of " << producer << " computer is used." << endl;
}

void Computer::input_pc()
{
    cout << "Please enter your pc producer:";
    cin >> producer;
    cout << "Please enter your pc gpu:";
    cin >> gpu;
    cout << "Please enter your pc cpu:";
    cin >> cpu;
    cout << "Please enter your pc ram:";
    cin >> ram;
}

void Computer::display()
{
    cout << "The computer is a " << producer << " comptuer with gpu " << gpu \
         << ", cpu " << cpu << " and ram of " << ram << " GB." << endl;
}

//类的访问

void visit_class()
{
    Computer pc1("Dell", "N1080", "Intel_i7", 8), pc2;
    pc1.display();
    cout << "----------" << endl;
    pc2.input_pc();
    pc2.display();
    Computer pc3(pc2);
    pc3.display();
    Computer *p = &pc1;
    p->display();
}


int main()
{
    visit_class();

    return 0;
}