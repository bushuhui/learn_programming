//10/18-10/20
//第七章 类

#include <iostream>
#include <string>

using namespace std;

//类的定义,构造函数

class Computer
{
    public:
        void input_pc();
        void display() const;
        void value_change(string, string, string, int);
        Computer();     //构造函数
        Computer(string p, string g, string c, int r); //重载
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

Computer::Computer(string p, string g, string c, int r): \
                   producer(p), gpu(g),cpu(c),ram(r)   //带参
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

void Computer::display() const  //常函数
{
    cout << "The computer is a " << producer << " comptuer with gpu " << gpu \
         << ", cpu " << cpu << " and ram of " << ram << " GB." << endl;
}

void Computer::value_change(string p = "", string g = "", string c = "", int r = 0)
{
    if (p!="")
        this->producer = p;
    if (g!="")
        this->gpu = g;
    if (c!="")
        this->cpu = c;
    if (r!=0)
        this->ram = r;
}

//类的访问

void visit_class()
{
    const Computer pc1("Dell", "N1080", "Intel_i7", 8);
    Computer pc2;
    pc1.display();
    cout << "----------" << endl;
    pc2.input_pc();
    pc2.display();
    Computer pc3(pc2);
    pc3.display();
    Computer *p = &pc2;
    p->display();
}

//对象引用

void object_quote(Computer &pc)
{
    pc.value_change("Apple", "N1050");
    pc.display();
}

//对象数组

void object_arr()
{
    Computer pcs[2]={Computer("Dell2", "N1080", "Intel_i7", 8), \
                     Computer("Acer", "N1050", "Intel_i5", 8)};
}

int main()
{
    //visit_class();
    Computer pc0("Dell", "N1080", "Intel_i7",8);
    //object_quote(pc0);
    object_arr();

    return 0;
}