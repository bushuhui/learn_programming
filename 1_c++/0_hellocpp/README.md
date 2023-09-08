# C++快速入门

20世纪80年代，AT&T Bell（贝尔）实验室的Bjarne Stroustrup博士及其同事在C语言的基础上成功开发出C++语言。C++语言是一种混合型语言，它保留了C语言所有的优点，同时又增添了面向对象的编程机制，我们可以将C++语言视为C语言的改进和扩展。

基于C语言开发的C++语言兼容C语言，因此用C语言编写的程序基本上可以不做改动地用于C++。相对于C语言，C++语言对C语言的功能做了一定的扩充，同时增添了面向对象编程机制。引入面向对象编程机制，主要是为了提高开发效率。

## C++能用来干什么

### 1) 软件开发

操作系统可以分为两块：内核以及内核以外的一些应用程序。内核用于控制最底层的硬件设备，而应用程序则是用于完成一系列的任务。应用程序是通过调用系统提供的接口（如windows API）操作硬件来实现一系列的功能。

要想从事应用软件开发，除了需要掌握基本的C++语法以外，还需要对windows系统及其他系统提供的API或SDK有一定的了解。与之相对应的岗位主要有软件开发工程师、算法工程师、架构工程师等。

### 2) 游戏开发

掌握了C++基本语法之后，开发游戏也依然是一个不错的选择，目前工业级别的3D游戏引擎仍然是用C或C++编写的。

虽然以个人能力无法去完成一个庞大的网络游戏，但是从简单开始，编写一些小游戏，然后逐渐深入，循序渐进并最终加入大型游戏开发团队还是非常好的一个选择。与之相应的就业岗位主要有游戏开发工程师、游戏引擎架构工程师等。

### 3) 多媒体开发

目前多媒体技术同样渗入到人们的日常生活中，音视频已经成为人们获取信息的一个非常重要的手段。音视频在传输过程中都是经过压缩并且按照一定规则打包过的。视频的编码技术从最开始的H.261到如今的H.265，经历了30多年的发展，而且实现代码全部是由C或C++实现。

最新的HEVC编码标准就是由C++代码实现，对此感兴趣的话在学完C++语法后，可以去ITU（国际电信联盟）官网去下载源码查看。与之相应的就业岗位有图像算法工程师、视频编码研发工程师、音视频转码工程师等。

### 4) 人工智能

人工智能、机器学习等方向也少不了C或C++语言的身影。虽然人工智能距离我们还有些远，但随着科技的飞速进步，将来能实现也未可知。

需要强调的是虽然C++语言可以从事的方向非常广泛，但是仅仅掌握C++语法是远远不够的，上述的应用领域C++语言是基础，进入这些领域还需要进一步深入学习相关领域的专业知识。千里之行，始于足下！下面我们将一一介绍C++的基本语法，以期能够帮助大家熟练掌握C++，为今后的发展奠定良好基础。


## 什么是面向对象

在面向对象的思想中，任何事物都可以被看做一个对象。每个对象都是完整的独立个体，它是由相关的属性和行为组合，与外界分离。因此，在面向对象编程中，程序员不在面对一个个函数和变量，而是放眼大局，面对一个个对象来看问题。

### 面向对象思想的特点

- **1. 封装** : 封装意味着把对象的属性和方法结合成一个独立的系统单位，并尽可能隐藏对象的内部细节。它是面向对象思想描述的基础，程序员不再是许多复杂函数和过程的实现，
    而是少数具有行为能力的个体实例。
- **2. 抽象** : 抽象的过程是对具体问题进行概括的过程，例如面包房提供一个抽象--"订单"。
- **3. 继承** : 子类对象拥有与其基类相同的全部属性和方法，称为继承。例如人的共有属性：鼻子、眼睛、嘴巴......方法：吃饭、睡觉。由此基础上可以整出亚洲人、欧洲人、非洲人。
        最后创造亚洲人小明。。。
- **4. 多态** : 多态是指在基类中定义的属性和行为被子类继承后，可以具有不同的数据类型或者表现行为等特性。

## 数据类型
首先是数组，然后是指针，最后是结构。
### 数组
数组名是指针常量，可以在声明中初始化，但不能在赋值语句中整体赋值：
```
char a[10]= "hello"; //正确
char a[10];
a[10]="hello";//错误
```

### 指针
地址是计算机内存中的某个位置，而指针是专门用来存放地址的特殊类型变量，变量的地址用取址操作符&取得。
一般情况下我们用下边的形式来声明指针变量：
``` 
int *p;
int pp=123;
p=&pp;
```
指针不仅能在声明中初始化，而且能在赋值语句中整体赋值。
```
char *p= "hello"; //正确
char *p;
p="hello";//正确
```

>**注意：** 星号有两种用途，第一种用于创建指针：int *mypointer=&myInt 是创建指针变量mypointer, 没有起到解索引的作用；第二种是对指针进行解引用： 
*mypointer=3998, 将myInt的值改为3998。
>C++允许指针群有同样的值：
```
int *p1=&myInt
int *p2=&myInt
```

常见指针运算表达式比较：
p++和p+1：指针p++结果为p指向下一元素；p++结果为下一元素的指针，但p本身不变。
y=*p+1和y=*(p+1): *p+1为p所指对象内容加1；*(p+1)为p指针加一，并取结果指针所指对象内容。

数组和指针：
```
#include <iostream>

int main() {
    int a[5] = { 1,2,3,4,5 };
    int* pa;
    pa = &a[0]; //正确，取数组第一个元素的地址。
    pa = a; //正确
    pa = &a; //错误
    std::cout << *pa<<std::endl;
    std::cout << a[0]<<std::endl;
    std::cout << *a<<std::endl; //以上均为取数组第一个元素

    std::cout << *pa <<"\t"<<pa << "\t" << pa + 2 << "\t" << *(pa + 2) << "\t" << *pa + 2<<std::endl; //分别输出为1，1的地址，3的地址，3,1+2=3。
    std::cout << pa++ << "\t"<< *pa << "\t" << pa << "\t" << pa + 2 << "\t" << *(pa + 2) << "\t" << *pa + 2<<std::endl; //分别输出为1的地址，2，2的地址，4的地址，4，2+2=4。
}

```
```python
const char *p="abcdef";

std::cout<<*p<<"\t"<<p<<"\t"<<p+2<<"\t"<<*(p+2)<<"\t"<<*p+2; //分别输出为a,abcdef,cdef,c,97+2=99
std::cout<<p++<<"\t"<<*p<<"\t"<<p<<"\t"<<p+2<<"\t"<<*(p+2)<<"\t"<<*p+2; //分别输出为bcdef,b,bcdef,def,d,98+2=100
```

### 结构
结构一种由程序员定义的、由其他变量类型组合而成的数据类型。定义一个结构：
```
struct Fish
{
    std::string name;
    std::string id;
    std::sex;
}

//创建一个Fish类的变量：
Fish Jingyu={"小金鱼"，"fish_0000",'M'}

//创建一个指向该结构的指针，指针的类型必须与指向的地址的变量的类型一致：
Fish *pJingyu=&Jingyu

//通过对指针进行解引用来访问相应的变量值：
(*pJingyu).name="鲤鱼"；
(*pJingyu).id="fish_0001"

//第二种方法：
pJingyu->name="草鱼"；
pJingyu->id="fish_0002";

std::cout<<(*pJingyu).name<<std::endl;
std::cout<<(*pJingyu).id<<std::endl;
std::cout<<pJingyu->name<<std::endl;
std::cout<<pJingyu->id<<std::endl;
```
## 类和对象
类是一个模型，当我们从这个类创建实例的时候，也就是对象本身。对象的内部可以是变量和函数，而结构通常只由各种变量组成。
创建第一个类：
```
class Car //类的名字大写
{
public:
    std::string color;
    std::string engine;
    float gas_tank;
    unsigned int Wheel;
    void fill_tank(float liter);
   
}; //声明变量之前需要“public”,类声明末尾必须有分号

void Car::fill_tank(float liter)
{ 
    gas_tank+=liter;
}
```
### 构造器和析构器
构造器和通常方法的主要区别：
- 构造器的名字必须和它所在的类的名字一样
- 系统在创建某个类的实例时会第一时间自动调用这个类的构造器
- 构造器永远不会返回任何值

创建构造器需要把它的声明添加到类里：
```
class Car{
    Car(void);
};
Car::Car(void){
    color="white";
    engine="V8";
    wheel =4;
    gas_tank=FULL_GAS;
}
```
从前面知道，在创建对象时，系统都会自动调用一个特殊的方法，即构造器。相应地，在销毁一个对象时，系统会调用另一个特殊方法达到对应效果。
一般来说，构造器用来完成事先的初始化和准备工作（申请分配内存）, 析构器用来完成事后必须的清理工作（清理内存）。
析构器有着和构造器/类一样的名字，前面多了一个波浪符“~”前缀。
```
class Car{
    Car(void);
    ~Car();
};
```
>**注意：** 析构器永远不会返回任何值；析构器不带参数。

## 类成员函数
C++语言可以看成是C语言的扩展和改进，相对于C语言，C++语言主要是增添了面向对象的特性。类（Class）则是C++面向对象编程的实现方式。

无论是何种编程语言，进行面向对象程序设计都将是从类的设计开始的。什么是类呢？其实很简单，我们可以理解为一种用户自定义的数据类型，类似于C语言里面的结构体（struct），在本章最后我们将对比类和结构体之间的异同。

首先我们来了解一下类的声明，先来看一个例子。

[例1] 一个最简单的类声明：

```c++
    class student
    {
        //可以在此处声明类成员变量和成员函数
    };
```

在例1中创建了一个student类，可以在该类中声明student类的成员变量和成员函数，用于描述student的各方面特性，例如姓名、学号、年龄等信息。

在例1中class是C++关键字，也是用于类声明的关键字。紧接class关键字之后的是我们自定义的类名student。

例1中的类定义我们可以理解为我们定义了一种新的数据类型，该数据类型的标识符为student（这个类似于int是C++中整形的标识符）。

特别要注意的一点是，在类声明结束处右括号“}”后面右一个分号“;”，这个分号一定不能忘记，它是类声明的一部分。如果漏掉则会在程序编译不通过。


声明了student数据类型之后，我们就可以用其定义变量了，如：
```c++
    student LiLei;  //创建对象
```
在这一条语句中就利用student数据类型声明了一个LiLei的变量，这和
```c++
    int a;  //定义整形变量
```
语句定义了一个整型变量表达的意思是类似的。而LiLei这个变量我们称之为student类的对象。


在用类定义对象的时候，一定要先给出类声明，这就好比用某种自定义数据类型来定义变量的时候，我们必须要先给出该数据类型的声明一样。由于C++里面本身集成一些常用数据类型，如int、bool、double等，所以在用这些数据类型声明变量时不需要再由我们自己给出类型声明了。

在定义类的对象时，class关键字可要可不要，但通常出于习惯我们通常都会省略掉class关键字。

定义类对象时，除了能定义单个变量以外，用类定义一个数组或者指针都是可行的。

[例2] class关键字可要可不要：
```c++
    class student LiLei; //正确
    student LiLei;     //同样正确
```
定义类对象时，除了能定义单个变量以外，用类定义一个数组或者指针都是可行的。

[例3] 定义对象数组或指针：
```c++
    student all_student[1000];
    student * pointer;
```
在例3中，我们定义了一个all_student数组，该数据拥有1000个元素，每一个元素都是student类型。此外，我们定义了一个student类型的指针pointer，该指针可以指向student类型的变量，其用法跟普通指针是一样的。

类是一种数据类型，该类型类似于普通的数据类型，但是又有别于普通的数据类型。类这种数据类型是一个包含成员变量和成员函数的一个集合。下面是student类的定义。

[例1] 类可以包含成员变量和成员函数：
```c++
    class student
    {
        char name[20];  //姓名
        int id_num;     //学号
        int age;        //年龄
        char sex;       //性别
        void set_age(int a);
        int get_age();
    };
```c++
本例声明了类student，并且在student类中声明了四个成员变量：name、id_num、age和sex。这四个成员变量用于描述student特性。除此之外我们还在类中定声明了两个函数，set_age函数和get_age函数，这两个函数是student类的成员函数，这两个函数只给出了声明，未给出定义。

有两种方法可以给出成员函数的定义：
1.在类内部进行函数的声明和定义，此种方式我们成为inline，也即内联定义。inline是C++关键字，专门用于表示内联；


2.在类内进行函数声明，在类外部进行函数定义。

下面我们分别给出两种情况的示例。

[例2] 在类内部进行函数的声明和定义：
```c++
    class student
    {
        char name[20];  //姓名
        int id_num;     //学号
        int age;        //年龄
        char sex;       //性别
        void set_age(int a){age = a;}
        int get_age(){return age;}
    };
```
在本例中，两个成员函数均是在类声明内部进行声明和定义的，因此这两个函数是inline类型的。
内联函数可以通知编译器在编译阶段用成员函数set_age和get_age的函数体替换掉所有调用该函数的代码，这样替换后的代码将不会再出现对这个函数的调用的代码。通过直接的替换可以在一定程度上提高程序运行效率，通常只是用于一些简短函数。

[例3] 在类内部声明函数，在类外部定义函数：
```c++
    class student
    {
        char name[20];  //姓名
        int id_num;     //学号
        int age;        //年龄
        char sex;       //性别
        void set_age(int a);
        int get_age()const;
    };
    //在类外部定义set_age函数
    void student::set_age(int a)
    {
        age = a;
    }
    //在类外部定义get_age函数
    int student::get_age()const
    {
        return age;
    }
```
本例中set_age函数和get_age函数在类声明内部仅有声明部分，而无定义部分，其函数体在类声明之外定义。本例中定义函数采用了域解析符 ::。

在类内声明函数，如果在函数声明时使用inline关键字，如例4所示，则可以将类内声明类外定义的函数强制转换为内联函数。

[例4] 强制转换为内联函数：
```c++
    class student
    {
        char name[20];  //姓名
        int id_num;     //学号
        int age;        //年龄
        char sex;       //性别
        inline void set_age(int a);
        inline int get_age();
    };
    //在类外部定义set_age函数
    void student::set_age(int a)
    {
        age = a;
    }
    //在类外部定义get_age函数
    int student::get_age()
    {
        return age;
    }
```
在例4中，student类中声明函数set_age和get_age时都使用了inline关键字，这就使得这两个函数也成为了内联函数，尽管它们是在类外进行定义函数体的。


## 继承
### C++继承的概念及语法
继承是类与类之间的关系，是一个很简单很直观的概念，与现实世界中的继承（例如儿子继承父亲财产）类似。

继承可以理解为一个类从另一个类获取方法（函数）和属性（成员变量）的过程。如果类B继承于类A，那么B就拥有A的方法和属性。被继承的类称为父类或基类，继承的类称为子类或派生类。

在上一章中我们例举了不少book类相关的示例，book类中有两个成员变量：title和price，即书的名字和价格。如果此时我们要按照编程语言将这些书进行分类，此时我们需要第三个成员变量language，这个时候我们没有必要重新设计一个全新的类，只需要在book类的基础上加上language属性及其相关的方法即可。

此时就可以将我们需要的codingbook类继承book类就可以得到book类的成员变量及成员函数，继承后在添加需要的language属性和相关的方法。新类codingbook叫做book类的派生类或子类，而原有的book类则称为基类。派生类codingbook除了能够拥有基类book的所有数据成员和成员函数之外，还可以拥有基类没有的language成员变量及其相关成员函数。

由于派生类可以将基类的代码继承过来，无需重新设计，因而继承解决了代码重用的问题，大大提高了软件的开发效率。同时如果这些代码在基类中运行无误，则继承之后到派生类中运行也是不会有问题的。

继承并非只能进行一层，可以是任意层次的。比如codingbook继承自book类，如果我们需要对codingbook类继续添加某一新属性时，同样可以设计一个类继承自codingbook类。

从book类中派生出codingbook类的语法如下例所示。

例1：

```
enum language{cpp, java, python,javascript, php, ruby};
class book
{
public:
    void setprice(double a);
    double getprice()const;
    void settitle(char* a);
    char * gettitle()const;
    void display();
private:
    double price;
    char * title;
};
class codingbook: public book
{
public :
    void setlang(language lang);
    language getlang(){return lang;}
private:
    language lang;
};
```
为了方便起见，我们先在类定义前声明了一个全局的枚举类型language，用于表示编程语言。book类我们已经很熟悉了，关键是codingbook类的定义。在定义codingbook类时多出了“: public book”，除此之外codingbook类的定义和上一章介绍的类定义方法没有什么差别。其中关键字public指明继承方式属于公有继承，book为被继承的类名。采用公用继承方式，则基类的公有成员变量和成员函数的属性继承到派生类后不发生变化。例如book类的公有的setprice和settitle成员函数继承到codingbook类后，这两个成员变量的属性仍将是public属性。如果在继承过程中不指名继承方式时，编译器系统会默认继承方式为private或protected属性。

在本例中因为已经定义过一个book类，具有book类的基本属性：书名和书的价格。现在需要一个新的类codingbook来描述编程类书籍，为此我们继承book类中的所有成员及成员函数，并新增language属性及相应的操作函数。虽然我们可以继承到book类的私有成员，但是book类的私有成员变量在派生类中我们是无法直接访问的，只能通过间接的方式访问。间接访问则是通过getprice、gettitle、setprice和settitle函数来实现的，因为这些函数在派生类中是public属性的。

### 继承方式
从基类派生出派生类，派生类继承基类的继承方式有三种：public、protected和private。在未指定的情况下编译器会默认继承方式为protected或private方式。

1) public继承方式

基类中所有public成员在派生类中为public属性；
基类中所有protected成员在派生类中为protected属性；
基类中所有private成员在派生类中不可访问。
具体示例可以参考上一节中的例1，在此就不再重新举例了。
2) protected继承方式

基类中的所有public成员在派生类中为protected属性；
基类中的所有protected成员在派生类中为protected属性；
基类中的所有private成员在派生类中仍然不可访问。

例1：

```
enum language{cpp, java, python,javascript, php, ruby};
class book
{
public:
    void setprice(double a);
    double getprice()const;
    void settitle(char* a);
    char * gettitle()const;
    void display();
private:
    double price;
    char * title;
};
class codingbook: protected book
{
public :
    void setlang(language lang);
    language getlang(){return lang;}
private:
    language lang;
};
```

3) private继承方式

基类中的所有public成员在派生类中均为private属性；
基类中的所有protected成员在派生类中均为private属性；
基类中的所有private成员在派生类中均不可访问。

例2：

```
enum language{cpp, java, python,javascript, php, ruby};
class book
{
public:
    void setprice(double a);
    double getprice()const;
    void settitle(char* a);
    char * gettitle()const;
    void display();
private:
    double price;
    char * title;
};
class codingbook: private book
{
public :
    void setlang(language lang);
    language getlang(){return lang;}
private:
    language lang;
};
```
### 改变基类成员在派生类中的访问属性
使用using声明可以改变基类成员在派生类中的访问属性。我们知道基类的公有成员经过公有继承，在派生类中其属性为public的，但是通过using 声明，我们可以将其改为private或protected属性。

例1：

```
enum language{cpp, java, python,javascript, php, ruby};
class book
{
public:
    void setprice(double a);
    double getprice()const;
    void settitle(char* a);
    char * gettitle()const;
    void display();
private:
    double price;
    char * title;
};
class codingbook: public book
{
public :
    void setlang(language lang);
    language getlang(){return lang;}
private:
    language lang;
        using book::setprice;
};
```
通过例1这样的定义，则下面的主函数就会编译错误，在think类对象调用setlang和settitle函数时都不会有问题，因为这两个函数的属性为public，可以访问。唯独setprice函数通过using声明后，由public属性变为了private属性了。

```
int main()
{
    codingbook think;
    think.setlang(cpp);
    think.settitle("Thinking in C++");
    think.setprice(78.9);  //compile error
    return 0;
}
```
###名字隐藏
如果派生类中新增一个成员变量，该成员变量与基类中的成员变量同名，则新增的成员变量就会遮蔽从基类中继承过来的成员变量。同理，如果派生类中新增的成员函数与基类中的成员函数同名，则该新增的成员函数就会遮蔽从基类中继承过来的成员函数。

例1：

```
#include<iostream>
using namespace std;
class basic
{
public:
    void setx(int a){x = a;}
    void sety(int b){y = b;}
    int getx(){return x;}
    int gety(){return y;}
private:
    int x;
    int y;
};
class derived : public basic
{
public:
    void setx(char *a){x = a;}
    char* getx(){return x;}
private:
    char * x;
};
int main()
{
    derived d1;
    d1.setx("class");   //OK
    d1.setx(50);        //compile error
    d1.basic::setx(50); //OK
    return 0;
}

```
在本例中定义了一个基类basic，之后通过继承basic类派生出derived类。需要注意的是在basic类中定义了一个成员变量x，该变量是int型，与之对应的成员函数是setx和getx函数。而派生类中同样定义了一个成员变量x，而它是char指针类型，与之对应的成员函数是setx和getx函数。在主函数中，定义了derived类的对象d1，我们在调用setx(char *)函数时，没有问题。接着又调用从基类中继承过来的setx(int)函数，结果编译出错。最后通过类名来调用基类继承过来的setx(int)函数，编译通过。在派生类derived中，setx(char *)与基类继承过来的setx(int)函数同名，如此一来，派生类新增的函数setx(char *)遮蔽了从基类继承而来的setx(int)函数，如此一来通过d1.setx(50)调用setx(int)是不成功的，故而出现编译错误，正确的调用方法是通过类名来调用：d1.basic::setx(int)。

从上例中，我们可以看出被遮蔽了的基类的成员变量或成员函数并非是没有继承过来，而仅仅是被派生类的同名成员变量和成员函数给遮蔽了，调用的时候需要用到类名加上域解析操作符。
### 间接继承
假设类C继承自类B，类B继承自类A。那么类C中的除了能够继承B类的成员函数和成员变量外，同样也能继承B类继承自A类的所有成员。换言之，类C可以继承来自类A的所有成员。因此继承既可以是直接继承，也可以是间接继承。

例1：

```
class A
{
public:
    int getx(){return x;}
    void setx(int a){x = a;}
private:
    int x;
};
class B : public A
{
public:
    int gety(){return y;}
    void sety(int b){y = b;}
private:
    int y;
};
class C : public B
{
public:
    int getz(){return z;}
    void setz(int c){z = c;}
private:
    int z;
};
```
在本例中，先定义了类A，然后通过派生定义了类B，之后再派生出类C。B类和C类都有自己新增的成员变量和成员函数。

### 继承机制下的构造函数

在前一章节中，我们介绍了构造函数的功能和用法，派生类同样有构造函数。当我们创建一个派生类对象的时候，基类构造函数将会被自动调用，用于初始化派生类从基类中继承过来的成员变量。而派生类中新增的成员变量则需要重新定义构造函数用于初始化了。

例1：

```
#include<iostream>
using namespace std;
class book
{
public:
    book();
    book(char* a, double p = 5.0);
    void setprice(double a);
    double getprice()const;
    void settitle(char* a);
    char * gettitle()const;
    void display();
private:
    double price;
    char * title;
};
class book_derived :public book
{
public:
    void display();
};
book::book(char* a, double p) 
{
    title = a;
    price = p;
}
book::book()
{
    title = "NoTitle";
    price = 0.0;
}
void book::setprice(double a)
{
    price = a;
}
double book::getprice()const
{
    return price;
}
void book::settitle(char* a)
{
    title = a;
}
char * book::gettitle()const
{
    return title;
}
void book::display()
{
    cout<<"The price of "<<title<<" is $"<<price<<endl;
}
void book_derived::display()
{
    cout<<"The price of "<<gettitle()<<" is $"<<getprice()<<endl;
}
int main()
{
    book_derived b;
    b.display();
    return 0;
}
```
在本例中定义了book_derived类，该类没有自身的成员变量，类中所有成员变量都继承自book类，类中成员函数仅有一个display函数，该函数遮蔽了基类book中的display函数。在主函数中定义派生类的对象b，之后调用派生类的display函数，程序运行结果为：“The price of NoTitle is $0”。

从这例1中，我们不难看出派生类在创建对象时会自动调用基类构造函数。如果像例1这种情况，派生类中没有新增成员变量，基类的构造函数功能已经满足派生类创建对象初始化需要，则派生类则无需重新自定义一个构造函数，直接调用基类构造函数即可。如果派生类中新增了成员变量，这时如果需要在创建对象时就进行初始化则需要自己设计一个构造函数，具体见例2。

例2：

```
#include<iostream>
using namespace std;
enum language{none, cpp, java, python, javascript, php, ruby};
class book
{
public:
    book();
    book(char* a, double p = 5.0);
    void setprice(double a);
    double getprice()const;
    void settitle(char* a);
    char * gettitle()const;
    void display();
private:
    double price;
    char * title;
};
class codingbook: public book
{
public :
    codingbook():book(){lang = none;}
    codingbook(language lang, char * t, double p);
    void setlang(language lang);
    language getlang(){return lang;}
    void display();
private:
    language lang;
};
book::book(char* a, double p) 
{
    title = a;
    price = p;
}
book::book()
{
    title = "NoTitle";
    price = 0.0;
}
void book::setprice(double a)
{
    price = a;
}
double book::getprice()const
{
    return price;
}
void book::settitle(char* a)
{
    title = a;
}
char * book::gettitle()const
{
    return title;
}
void book::display()
{
    cout<<"The price of "<<title<<" is $"<<price<<endl;
}
void codingbook::setlang(language lang)
{
    this->lang = lang;
}
codingbook::codingbook(language lang, char * t, double p):book(t,p)
{
    this->lang = lang;
}
void codingbook::display()
{
    book::display();
    cout<<"The language is "<<lang<<endl;   
}
int main()
{
    codingbook cpp;
    cpp.display();
    codingbook java(java, "Thinking in Java", 59.9);
    java.display();
    return 0;
}
```
本例中定义了两个类book类和codingbook类，codingbook类是book类的派生类。在codingbook类中新增了一个language成员变量，为此必须重新设计新的构造函数。在本例中book类中有一个默认构造函数和一个带参数的构造函数，codingbook类中同样声明了两个构造函数，一个默认构造函数和一个带参数的构造函数，默认构造函数显式调用基类的默认构造函数，带参构造函数显式调用基类的带参构造函数。在主函数中定义了codingbook类的对象cpp，该对象调用codingbook类的默认构造函数，codingbook类中的默认构造函数先会调用基类的默认构造函数将title和price进行初始化，之后才会执行自身函数体中的内容。之后又定义了codingbook类对象java，该对象在定义时后面接有三个参数，很明显是需要调用codingbook类的带参构造函数，其中java参数用于初始化lang成员变量，而后两个参数则用于初始化从基类继承过来的title和price两个成员变量，当然初始化顺序依然是先调用基类的带参构造函数初始化title和price，然后再执行自身函数体中的初始化代码初始化lang成员变量。

最后程序运行结果如下：

```
The price of NoTitle is $0
The language is 0
The price of Thinking in Java is $59.9
The language is 2
```
在这个例子中language没有显示为java或者cpp，只显示为0和2，这个熟悉枚举类型的应该都清楚，枚举类型在本例中其实就是从0开始的int类型。

从例2中，我们可以很清楚的看到，当我们创建派生类对象时，先由派生类构造函数调用基类构造函数，然后再执行派生类构造函数函数体中的内容，也就是说先执行基类构造函数，然后再去执行派生类构造函数。如果继承关系有好几层的话，例如A类派生出B类，B类派生出C类，则创建C类对象时，构造函数的执行顺序则为A的构造函数，其次是B的构造函数，最后是C类的构造函数。构造函数的调用顺序是按照继承的层次，自顶向下，从基类再到派生类的。

例3：

```
#include<iostream>
using namespace std;
class base
{
public:
    base(){x = 0; y = 0; cout<<"base default constructor"<<endl;}
    base(int a, int b){x = a; y = b; cout<<"base constructor"<<endl;}
private:
    int x;
    int y;
};
class derived: public base
{
public:
    derived():base(){z = 0; cout<<"derived default constructor"<<endl;}
    derived(int a, int b, int c):base(a,b){z = c; cout<<"derived constructor"<<endl;}
private:
    int z;
};
int main()
{
    derived A;
    derived B(1,2,3);
    return 0;
}
```
本例中定义了两个类，基类base中定义了一个默认构造函数和一个带参数的构造函数。派生类derived中同样定义了两个构造函数，这两个构造函数一个为默认构造函数，一个为带参构造函数。派生类中的默认构造函数显式调用基类默认构造函数，带参构造函数显式调用基类的带参构造函数。我们在主函数中定义了派生类的两个对象，这两个对象一个是调用派生类的默认构造函数，另一个调用派生类的带参构造函数。

这个程序运行结果如下：

```
base default constructor
derived default constructor
base constructor
derived constructor
```
从运行结果可以看出创建对象时先是执行基类的构造函数，然后再是执行拍摄呢类构造函数。构造函数执行顺序是按照继承顺序自顶向下执行。



### 派生类构造函数调用规则

派生类构造函数可以自动调用基类的默认构造函数而无需显式调用。例如在上一节例2中，我们如果将condingbook类中的默认构造函数codingbook():book(){lang = none;}语句修改为codingbook(){lang = none;}，则这个程序运行结果依然保持不变，因为派生类的构造函数会自动调用基类的默认构造函数。

派生类构造函数可以自动调用基类的默认构造函数，但是前提是默认构造函数必须存在。通常情况下，默认构造函数系统会自动生成的，但是如果在基类中，我们自己定义了一个带参数的构造函数，这个时候，系统是不会为基类自动生成默认构造函数的，这个时候派生类则无法自动调用基类的默认构造函数了，因为基类根本就不存在默认构造函数。遇到这种情况有两种解决方案：其一，在基类中定义一个默认构造函数（不带参数的构造函数），例如上一节中的例2；其二，派生类中的每一个构造函数都显式的调用基类中的带参构造函数。

例1：

```
class base
{
public:
    base(int a){x = a; y = 0;}
    base(int a, int b){x = a; y = b;}
private:
    int x;
    int y;
};
class derived: public base
{
public:
    derived(){z = 0;}
    derived(int c){z = c;}
private:
    int z;
};
```
我们来看一下这个例子，这个例子里面先定义了一个类base作为基类，基类中拥有两个成员变量x和y，同时定义了两个带参数的构造函数，两个都是带参构造函数，如此一来类base就不会自动生成默认构造函数了。再来看派生类定义，派生类中新增了成员变量z，并且定义了一个带参构造函数和一个默认构造函数。但是如此定义，编译器会提示语法错误，因为派生类的构造函数没有显示调用基类构造函数。解决这个问题的方法在上面说了，一个是在基类自己定义一个默认构造函数，另外一种方法是显示调用基类构造函数。当然在设计类的时候推荐使用后者，毕竟构造函数就是为了初始化成员变量的，如果不显式调用基类构造函数，则从基类中继承过来的成员变量将得不到初始化，这一般来说都不是我们所希望看到的。

同时，我们还建议在设计类的时候为每一个类设计一个默认构造函数，毕竟默认构造函数并不会妨碍构造函数的显式调用。通常我们还会遇到这样一种情况，派生类中并未显式定义构造函数，这个时候派生类中只有系统自动生成的默认构造函数，如此一来，如果我们不为基类设计一个默认构造函数，则程序就会编译出错。这种错误很玄妙，如果不小心还真是难以发现。为了避免这种情况的发生，我们建议为每一个类设计一个默认构造函数。

根据以上两点建议，我们将例1进行修改，正确代码如下。

例2：

```
#include<iostream>
using namespace std;
class base
{
public:
    base(){x = 0; y = 0;}
    base(int a){x = a; y = 0;}
    base(int a, int b){x = a; y = b;}
private:
    int x;
    int y;
};
class derived: public base
{
public:
    derived():base(){z = 0;}
    derived(int a, int b, int c):base(a,b){z = c;}
private:
    int z;
};
int main()
{
    derived A;
    derived B(1,2,3);
    return 0;
}

```
在这个例子中，我们将例1中出现的问题采用双管齐下的方式解决了，为基类定义了默认构造函数，并且在派生类中显式地调用基类中的构造函数。

总的来说，在创建派生类对象时，必须显式或隐式地调用基类的某一个构造函数，这一点非常重要。当然被调用的基类的构造函数可以是带参构造函数，也可以是默认构造函数。



### 继承机制下的析构函数
创建派生类对象时构造函数的调用顺序是按照继承顺序，先执行基类构造函数，然后再执行派生类的构造函数。但是对于析构函数，其调用顺序是正好相反的，即先执行派生类的构造函数，然后再执行基类的构造函数。

例1：

```
#include <iostream>
using namespace std;
class A
{
public:
    A(){cout<<"A constructor"<<endl;}
    ~A(){cout<<"A destructor"<<endl;}
};
class B: public A
{
public:
    B(){cout<<"B constructor"<<endl;}
    ~B(){cout<<"B destructor"<<endl;}
};
class C: public B
{
public:
    C(){cout<<"C constructor"<<endl;}
    ~C(){cout<<"C destructor"<<endl;}
};
int main()
{
    C test;
    return 0;
}
```
在本例中定义了三个类，C类继承自B类，B类继承自A类。在每个类中定义默认构造函数和析构函数。在主函数中我们定义了C类的一个对象，创建对象时各个类的构造函数会被调用，之后退出程序，各类的析构函数会被逐一调用。程序运行结果如下：

```
A constructor
B constructor
C constructor
C destructor
B destructor
A destructor
```
程序运行结果很好地说明了构造函数和析构函数的执行顺序。构造函数的执行顺序是按照继承顺序自顶向下的，从基类到派生类，而析构函数的执行顺序是按照继承顺序自下向上，从派生类到基类。

因为每一个类中最多只能有一个析构函数，因此调用的时候并不会出现二义性，因此析构函数不需要显式的调用。

### 多继承
在前面所有的例子中，派生类都只有一个基类，我们成这种情况为单继承。而在C++中一个派生类中允许有两个及以上的基类，我们称这种情况为多继承。单继承中派生类是对基类的特例化，例如前面中编程类书籍是书籍中的特例。而多继承中，派生类是所有基类的一种组合。

例1：
```
class teacher
{
public:
    void settitle(char *a){title = a;}
    char * gettitle(){return title;}
private:
    char * title; //职称
};
class cadre
{
public:
    void setpost(char *a){post = a;}
    char * getpost(){return post;}
private:
    char *post; //职务
};
class teacher_cadre: public cadre, public teacher
{
public:
    void setwages(int a){wages = a;}
    int getwages(){return wages;}
private:
    int wages; //工资
};
```
在本例中我们定义了三个类，一个是教师类，该类中有一个成员变量职称title；另一个类是干部类，这个类中有一个成员变量职务post；最后定义了一个类teacher_cadre，这个类是cadre和teacher类的派生类，它也有一个新增的成员变量wages，表示工资。很明显教职工干部teacher_cadre类是cadre类和teacher类的组合。

在多继承中，派生类继承了所有基类中的所有成员变量和成员函数，这些继承过来的成员变量及成员函数其访问规则与单继承是相同的，下面我们将例1中的teacher_cadre类中的所有成员及访问属性列于下表中。



### 虚基类
在多继承时很容易产生命名冲突问题，如果我们很小心地将所有类中的成员变量及成员函数都命名为不同的名字时，命名冲突依然有可能发生，比如非常经典的菱形继承层次。类A派生出类B和类C，类D继承自类B和类C，这个时候类A中的成员变量和成员函数继承到类D中变成了两份，一份来自A派生B然后派生D这一路，另一份来自A派生C然后派生D这一条路。

<div align=center>
![](http://www.weixueyuan.net/uploads/allimg/150208/8-15020R03Z5649.png)
</div>

例1：

```
class A
{
public:
    void setx(int a){x = a;}
    int getx(){return x;}
private:
    int x;
};
class B: public A
{
public:
    void sety(int a){y = a;}
    int gety(){return y;}
private:
    int y;   
};
class C: public A
{
public:
    void setz(int a){z = a;}
    int getz(){return z;}
private:
    int z;
};
class D: public B, public C
{
    //......
};
```
本例即为典型的菱形继承结构，类A中的成员变量及成员函数继承到类D中均会产生两份，这样的命名冲突非常的棘手，通过域解析操作符已经无法分清具体的变量了。为此，C++提供了虚继承这一方式解决命名冲突问题。虚继承只需要在继承属性前加上virtual关键字。

例2：

```
#include <iostream>
using namespace std;
class A
{
public:
    void setx(int a){x = a;}
    int getx(){return x;}
private:
    int x;
};
class B: virtual public A
{
public:
    void sety(int a){y = a;}
    int gety(){return y;}
private:
    int y;   
};
class C: virtual public A
{
public:
    void setz(int a){z = a;}
    int getz(){return z;}
private:
    int z;
};
class D: public B, public C
{
    //......
};
int main()
{
    D test;
    test.setx(10);
    cout<<test.getx()<<endl;
    return 0;
}
```
在本例中，类B和类C都是继承类A都是虚继承，如此操作之后，类D只会得到一份来自类A的数据。在本例的主函数中，定义了类D的对象test，然后通过该对象调用从类A间接继承来的setx和getx成员函数，因为B和C继承自类A采用的是虚继承，故通过D调用setx和getx不会有命名冲突问题，因为D类只得到了一份A的数据。

例1：

```c++
class A
{
public:
    void setx(int a){x = a;}
    int getx(){return x;}
private:
    int x;
};
class B: public A
{
public:
    void sety(int a){y = a;}
    int gety(){return y;}
private:
    int y;   
};
class C: public A
{
public:
    void setz(int a){z = a;}
    int getz(){return z;}
private:
    int z;
};
class D: public B, public C
{
    //......
};
```

本例即为典型的菱形继承结构，类A中的成员变量及成员函数继承到类D中均会产生两份，这样的命名冲突非常的棘手，通过域解析操作符已经无法分清具体的变量了。为此，C++提供了虚继承这一方式解决命名冲突问题。虚继承只需要在继承属性前加上virtual关键字。

例2：

```c++
#include <iostream>
using namespace std;
class A
{
public:
    void setx(int a){x = a;}
    int getx(){return x;}
private:
    int x;
};
class B: virtual public A
{
public:
    void sety(int a){y = a;}
    int gety(){return y;}
private:
    int y;   
};
class C: virtual public A
{
public:
    void setz(int a){z = a;}
    int getz(){return z;}
private:
    int z;
};
class D: public B, public C
{
    //......
};
int main()
{
    D test;
    test.setx(10);
    cout<<test.getx()<<endl;
    return 0;
}
```
在本例中，类B和类C都是继承类A都是虚继承，如此操作之后，类D只会得到一份来自类A的数据。在本例的主函数中，定义了类D的对象test，然后通过该对象调用从类A间接继承来的setx和getx成员函数，因为B和C继承自类A采用的是虚继承，故通过D调用setx和getx不会有命名冲突问题，因为D类只得到了一份A的数据。


## this指针和类的继承

### this指针
    在对象的世界里，有一个特殊的指针this, 例子：
```
class Human{
    char fishc;
    Human(char fishc);
};
Human::Human(char fishc){
    fishc=fishc;
}
```
    可以看到Human() 构造器有一个fishc的参数，它与Human类里的属性同名，但并没有错。如何让构造器知道哪一个是参数，哪一个是属性呢？
这时候需要this指针。
    -this->fishc=fishc;

### 类的继承
基类：
- 基类是可以派生出其他的类，也称为父类。比如Animal类是基类。
子类：
- 子类是从基类派生出来的类，比如Turtle类，Pig类是子类。
那么Animal类就拥有Turtle类和Pig类的共同特征：吃东西、睡觉。
这里把这些动作都抽象化为方法
- eat(), sleep();
假如swim()方法在Turtle类里实现，climb()方法在Pig类里实现
动物都有嘴巴, 嘴巴是名词不是动作，而不能翻译成类的方法。因此。我们将mouth转变为Aniaml类的一个成员变量（属性）
- class Pig: public Animal{.......}
```
#include <iostream>
#include<string>
class Animal{
public:
    std::string mouth;
    void eat();
    void sleep();
};

class Pig: public Animal{
public:
    void climb();
};

class Turtle: public Animal{
public:  
    void swim();
};

void Animal::eat()
{
    std::cout<<"I'm eatting!"<<std::endl;
}

void Animal::sleep()
{
    std::cout<<"I'm sleeping!"<<std::endl;
}

void Pig::climb()
{
     std::cout<<"I'm climbing!"<<std::endl;
}

void Turtle::swim()
{
     std::cout<<"I'm swimming!"<<std::endl;
}

int main(){
    Pig pig;
    Turtle turtle;
    pig.eat();
    turtle.eat();
    pig.climb();
    turtle.swim();
    return 0;
}
```
### 继承机制中的构造器和析构器
```
Animal::Animal(std::string theName){
    name=theName;
}
Pig::Pig(std::string theName): Animal(theName){
}
```
子类构造里的Animal(theName)含义是：调用Pig()构造器时（以theName作为参数），Animal()构造器也将被调用，其赋值动作在Animal()方法里。
先调用基类的构造函数，再对新定义成员进行初始化，最后执行派生类构造函数。
派生类析构函数的定义与基类无关，与没有继承关系的类中的析构函数定义相同。

```
Pig::~pig(){
    std::cout<<"已进入子类析构器"<<std::endl;
}
```

## 覆盖方法和重载函数
### 覆盖方法
当我们需要在基类里提供一个通用的函数，但在某个子类里需要修改这个方法的实现，在C++里覆盖可以做到。
```
#include <iostream>
#include<string>
class Animal{
public:
    Animal(std::string theName);
    void eat();
    void sleep();
protected:
    std::string name;
};

class Pig: public Animal{
public:
    Pig(std::string theName);
    void climb();
    void eat();
};

class Turtle: public Animal{
public:  
    Pig(std::string theName);
    void swim();
    void eat();
};
Animal::Animal(std::string theName){
    name= theName;
}
void Animal::eat()
{
    std::cout<<"I'm eatting!"<<std::endl;
}

void Animal::sleep()
{
    std::cout<<"I'm sleeping!"<<std::endl;
}

Pig::Pig(std::string theName): Animal(theName){
}
void Pig::climb()
{
     std::cout<<"I'm climbing!"<<std::endl;
}
//eat 方法的覆盖
void Pig::eat()
{    
     Animal::eat();
     std::cout<<name<<"正在吃鱼"<<std::endl;
}

Turtle::turtle(std::string theName): Animal(theName){
}
void Turtle::swim()
{
     std::cout<<"I'm swimming!"<<std::endl;
}
//eat 方法的覆盖
void Turtle::eat()
{    
     Animal::eat();
     std::cout<<name<<"正在吃猪肉"<<std::endl;
}
int main(){
    Pig pig("小猪猪");
    Turtle turtle("小乌龟");
    pig.eat(); //eat 方法的覆盖
    turtle.eat(); //eat 方法的覆盖
    pig.climb();
    turtle.swim();
    return 0;
}
```
### 重载方法
重载机制可以定义多个同名的方法（函数），只是他们的输入参数必须不同。
```
class Animal{
public:
    Animal(std::string theName);
    void eat();
    void eat(int eatCount);
    void sleep();
protected:
    std::string name;
};
void Animal::eat()
{
    std::cout<<"I'm eatting!"<<std::endl;
}
void Animal::eat(int eatCount)
{
    std::cout<<"我吃了"<<eatCount<<"碗混沌"<<std::endl;
}
```
## 友元关系
类的成员函数才能访问类的私有成员和保护成员，外部函数只能访问类的公有成员。但在某些情况下，需要在类的外部访问类的私有成员和保护成员。如果通过公有成员函数
进行访问，由于参数传递、类型检查和安全检查等需要时间上的开销，影响程序运行效率。为了解决这个问题，引入了友元。友元可以在类外部直接访问类的私有成员和保护成员。
只要在类声明里面的某个地方加上一条friend class**。

## 虚方法
引发问题：使用指向对象的指针，使用指针代替局部变量来容纳Pet对象。因为完全可以在没有创建变量的情况下为有关数据分配内存，也就是直接创建一个指针并让它指向新
分配的内存块：
```
int *p=new int;
*p=110;
std::cout<<*p;
delete p;
```

```
#include <iostream>
#include<string>
class Pet{
public:
    Pet(std::string theName);
    void eat();
    void sleep();
    void play();
protected:
    std::string name;
};

class Cat:public Pet{
public:
    Cat(std::string theName);
    void climb();
    void play();
};

class Dog:public Pet{
public:
    Cat(std::string theName);
    void bark();
    void play();
};

Pet::Pet(std::string theName){
    name= theName;
}

void Pet::eat()
{
    std::cout<<name<<"正在吃东西"<<std::endl;
}

void Pet::sleep()
{
    std::cout<<name<<"正在睡大觉"<<std::endl;
}

void Pet::play()
{
    std::cout<<name<<"正在玩儿"<<std::endl;
}

Cat::Cat(std::string theName): Pet(std::string theName){
 }

void Cat::climb()
{
    std::cout<<name<<"正在爬树"<<std::endl;
}
void Cat::play()
{
    Pet::play();
    std::cout<<name<<"玩毛线球"<<std::endl;
}

Dog::Dog(std::string theName): Pet(std::string theName){
 }

void Dog::bark()
{
    std::cout<<name<<"旺~旺"<<std::endl;
}
void Dog::play()
{
    Pet::play();
    std::cout<<name<<"正在追猫"<<std::endl;
}

int main()
{
Pet *cat=new Cat("加菲");
Pet *dog=new Dog("小黄");

cat->sleep();
cat->eat();
cat->play();

dog->sleep();
dog->eat();
dog->play();
}
```

cat和dog在编译时都是Pet类型指针，编译器认为两个指针调用的play()方法即Pet::play()方法，但是只有在运行的时候才为dog和cat分配Dog类型和Cat类型的指针。
它们在运行时分配的类型和它们在编译时的类型是不一样的。因此，需要虚方法，即在原型前加上virtual保留字。
- virtual void play();

## 错误处理
例如当计算阶乘的值超出计算机所表达的最大整数，输出错误数值但未报异常时，常用climits头文件#include<climits>。
用assert()函数帮助调试程序，利用它在某个程序里的关键假设不成立时立刻停止该程序的执行并报错，从而避免发生更严重的问题。
为了对付潜在编程错误（尤其时运行时的错误）,捕获异常是一种不同的方法，基本使用思路：
- 1. 安排try 去尝试某件事
- 2. 如果发生问题，用throm语句抛出一个异常
- 3. 再用catch语句去捕获这个异常并进行相应的处理。

## 避免内存泄漏
    内存泄漏情况之一：
- int *x;
- x=new int[3000];
- x=new int[4000];
- delete[] x;
- x=NULL;

3000个整型变量的地址遗失了。
情况之二：
用来保存内存块地址的指针变量作用域问题，例如：
```
void foo()
{
    My Class *x;
    x=new MyClass();
}
```
new MyClass()是没有作用域的地址，它存在于堆里，不能自动释放，只能delete释放。foo()函数结束时，指针变量x超出它的作用域，其值丢失，即new MyClass()指向的地址不见了，产生内存泄漏。所以，不应该让任何一个函数把自己局部变量的地址作为返回值。

解决方法：
- 1.在return 前插入delete x语句：
```
void foo()
{
    My Class *x;
    x=new MyClass();
    delete[] x;
    x=NULL;
    return;

}
```
- 2.让函数把内存块的地址返回给它的调用者：
```
void *foo()
{
    My Class *x;
    x=new MyClass();
    
    return x;

}
```

## 模板
这些模板可以没有任何类型：它可以处理的数据并不仅限于某种特定的数据类型。
## 函数模板
```
#include <iostream>
#include<string>

template<class T>//不是类
void swap(T &a, T &b){
    T tmp= a;
    a=b;
    b=tmp;
}

int main()
{
    int i1=100;
    int i2=200;
    swap(i1,i2);
    std::cout<<"i1="<<i1<<"i2="<<i2<<endl;
    std::string s1="abc";
    std::string s2="def";
    swap(s1,s2);
    std::cout<<"s1="<<s1<<"s2="<<s2<<endl;
}
```

## 类模板
基于模板的栈
```c++
#include<iostream>
#include<string>
template<class T>
class Stack{
public: 
    stack(unsigned int size=100);
    ~stack();
    void push(T value);
    T pop();
private:
    unsigned int size;
    unsigned int sp;
    T *data;
};

template<class T>
Stack<T>::stack(unsigned int size=100){
    this->size;
    data=new T[size];
    sp=0;
}

template<class T>
Stack<T>::~stack(){
    delete[] data;
}

template<class T>
void Stack<T>::push(T value){
    data[sp++]=value;
}

template<class T>
T Stack<T>::pop(){
   return data[--sp];
}


int main()
{
    Stack<int> intstack(100);
    intstack.push(1);
    intstack.push(2);
    intstack.push(3);
    
    std::cout<<intstack.pop()<<"\n";
    std::cout<<intstack.pop()<<"\n";
    std::cout<<intstack.pop()<<"\n";

    return 0;
}


```

​    

## 参考资料

* [一步一步学编程](https://gitee.com/pi-lab/learn_programming)
    * [c++基础](https://gitee.com/pi-lab/learn_programming/tree/master/1_c++)
    * [数据结构](https://gitee.com/pi-lab/learn_programming/tree/master/2_datastructure_algorithm)
    * [算法练习题](https://gitee.com/pi-lab/learn_programming/tree/master/3_code_practice)
    * [小项目练习](https://gitee.com/pi-lab/learn_programming/tree/master/4_projects)
    * [编程高级技巧](https://gitee.com/pi-lab/learn_programming/tree/master/5_advanced)





