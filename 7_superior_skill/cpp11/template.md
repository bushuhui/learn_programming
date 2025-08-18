# Template

## 函数模版

函数模板是可以使用泛型类型的特殊函数。这使我们能够创建一个功能模板，其功能可以适应多种类型或类，而无需为每种类型重复整个代码。 

在 C++ 中，这可以使用模板参数来实现。模板参数是一种特殊类型的参数，可用于将类型作为参数传递：就像常规函数参数可用于将值传递给函数一样，模板参数也允许将类型传递给函数。这些函数模板可以像使用任何其他常规类型一样使用这些参数。 声明带有类型参数的函数模板的格式是：

```c++
template <class identifier> function_declaration; 
template <typename identifier> function_declaration;
```

  两个原型之间的唯一区别是关键字 class 或关键字 typename 的使用。它的用法是模糊的，因为这两个表达式具有完全相同的含义并且以完全相同的方式运行。 例如，要创建一个返回两个对象中较大者的模板函数，我们可以使用：

```c++
template <class myType>
myType GetMax (myType a, myType b) {
 return (a>b?a:b);
}
```

我们创建了并将 myType 作为其模板参数的模板函数。此模板参数表示尚未指定的类型，但可以在模板函数中使用。如您所见，函数模板 GetMax 返回此仍未定义类型的两个参数中的较大者。 要使用此函数模板，我们使用以下格式进行函数调用：` function_name <type> (parameters)`； 使用例子如下：

```c++
int x,y;
GetMax <int> (x,y);
```

将通用类型 `myType` 用作 `GetMax` 的参数的特定情况下，编译器可以自动找出必须实例化的数据类型，而无需在尖括号内显式指定它,如下：

```c++
int i=5, j=6, k;
long l=10, m=5, n;
k=GetMax(i,j);
n=GetMax(l,m);
```



## 类模板

我们也有可能编写类模板，这样一个类就可以拥有使用模板参数作为类型的成员。例如：

```c++
// class templates
#include <iostream>
using namespace std;

template <class T>
class mypair {
    T a, b;
  public:
    mypair (T first, T second)
      {a=first; b=second;}
    T getmax ();
};

template <class T>
T mypair<T>::getmax ()
{
  T retval;
  retval = a>b? a : b;
  return retval;
}

int main () {
  mypair <int> myobject (100, 75);
  cout << myobject.getmax();
  return 0;
}
```

这一部分是类的实例化

```c++
mypair <int> myobject (100, 75);
```

定义了类型并自动调用回调函数。

## 模版特化

如果我们想在将特定类型作为模板参数传递时为模板定义不同的实现，我们可以声明该模板的特化。 例如，假设我们有一个名为 mycontainer 的非常简单的类，它可以存储任何类型的一个元素，并且它只有一个名为 increase 的成员函数，用于增加它的值。但是我们发现当它存储一个 char 类型的元素时，使用函数成员大写的完全不同的实现会更方便，所以我们决定为该类型声明一个类模板特化：

```
// template specialization
#include <iostream>
using namespace std;

// class template:
template <class T>
class mycontainer {
    T element;
  public:
    mycontainer (T arg) {element=arg;}
    T increase () {return ++element;}
};

// class template specialization:
template <>
class mycontainer <char> {
    char element;
  public:
    mycontainer (char arg) {element=arg;}
    char uppercase ()
    {
      if ((element>='a')&&(element<='z'))
      element+='A'-'a';
      return element;
    }
};

int main () {
  mycontainer<int> myint (7);
  mycontainer<char> mychar ('j');
  cout << myint.increase() << endl;
  cout << mychar.uppercase() << endl;
  return 0;
}
```

这是类模板特化中使用的语法：

```c++
template <> class mycontainer <char> { ... };
```

当我们为模板类声明特化时，我们还必须定义它的所有成员，即使是那些与通用模板类完全相同的成员，因为从通用模板到特化的成员没有“继承”。

除了前面有 class 或 typename 关键字（表示类型）的模板参数外，模板还可以具有常规类型参数，类似于函数中的参数。例如，看一下这个用于包含元素序列的类模板：

```c++
// sequence template
#include <iostream>
using namespace std;

template <class T, int N>
class mysequence {
    T memblock [N];
  public:
    void setmember (int x, T value);
    T getmember (int x);
};

template <class T, int N>
void mysequence<T,N>::setmember (int x, T value) {
  memblock[x]=value;
}

template <class T, int N>
T mysequence<T,N>::getmember (int x) {
  return memblock[x];
}

int main () {
  mysequence <int,5> myints;
  mysequence <double,5> myfloats;
  myints.setmember (0,100);
  myfloats.setmember (3,3.1416);
  cout << myints.getmember(0) << '\n';
  cout << myfloats.getmember(3) << '\n';
  return 0;
}
```

也可以为类模板参数设置默认值或类型。例如，如果先前的类模板定义是：

```c++
template <class T=char, int N=10> class mysequence {..};
```

我们可以通过声明以下内容来使用默认模板参数创建对象：

```c++
mysequence<> myseq;
```

## 模版偏特化

当存在多个类型时，可以给一部分进行特化

```c++
template<class T1, class T2, int I>
class A {};             // primary template
 
template<class T, int I>
class A<T, T*, I> {};   // #1: partial specialization where T2 is a pointer to T1
 
template<class T, class T2, int I>
class A<T*, T2, I> {};  // #2: partial specialization where T1 is a pointer
 
template<class T>
class A<int, T*, 5> {}; // #3: partial specialization where
                        //     T1 is int, I is 5, and T2 is a pointer
 
template<class X, class T, int I>
class A<X, T*, I> {};   // #4: partial specialization where T2 is a pointer
```

标准库中偏特化的例子包括 `std::unique_ptr`，它对数组类型有偏特化。

```c++
template <class T,class Deleter> 
class unique_ptr<T[], Deleter>;
```

 偏特化的成员与主模板的成员无关。 部分特化成员的显式（完全）特化的声明方式与主模板的显式特化相同。

```c++
template<class T, int I> // primary template
struct A
{
    void f(); // member declaration
};
 
template<class T, int I>
void A<T, I>::f() {}      // primary template member definition
 
// partial specialization
template<class T>
struct A<T, 2>
{
    void f();
    void g();
    void h();
};
 
// member of partial specialization
template<class T>
void A<T, 2>::g() {}
 
// explicit (full) specialization
// of a member of partial specialization
template<>
void A<char, 2>::h() {}
 
int main() {
    A<char, 0> a0;
    A<char, 2> a2;
    a0.f(); // OK, uses primary template’s member definition
    a2.g(); // OK, uses partial specialization's member definition
    a2.h(); // OK, uses fully-specialized definition of
            // the member of a partial specialization
    a2.f(); // error: no definition of f() in the partial
            // specialization A<T,2> (the primary template is not used)
}
```

如果主模板是另一个类模板的成员，则其偏特化是封闭类模板的成员,可以看下面的例子：

```c++
template<class T> struct A // enclosing class template
{
    template<class T2>
    struct B {};      // primary member template
    template<class T2>
    struct B<T2*> {}; // partial specialization of member template
};
 
template<>
template<class T2>
struct A<short>::B {}; // full specialization of primary member template
                       // (will ignore the partial)
 
A<char>::B<int*> abcip;  // uses partial specialization T2=int
A<short>::B<int*> absip; // uses full specialization of the primary (ignores partial)
A<char>::B<int> abci;    // uses primary
```



模板类或函数的实现（定义）必须与其声明在同一个文件中。这意味着我们不能在单独的头文件中分离接口，并且我们必须在使用模板的任何文件中包含接口和实现。 由于在需要时实例化模板之前不会生成任何代码，因此编译器准备允许在项目中多次包含具有声明和定义的同一模板文件，而不会产生链接错误。

## template Parameter Pack（C++11）

模板参数包是接受零个或多个模板参数（非类型、类型或模板）的模板参数。函数参数包是接受零个或多个函数参数的函数参数。 具有至少一个参数包的模板称为可变参数模板。

可以使用任意数量的模板参数实例化可变类模板：

```c++
template<class... Types>
struct Tuple {};
 
Tuple<> t0;           // Types contains no arguments
Tuple<int> t1;        // Types contains one argument: int
Tuple<int, float> t2; // Types contains two arguments: int and float
Tuple<0> t3;          // error: 0 is not a type
```

可以使用任意数量的函数参数调用可变参数函数模板

```c++
template<class... Types>
void f(Types... args);
 
f();       // OK: args contains no arguments
f(1);      // OK: args contains one argument: int
f(2, 1.0); // OK: args contains two arguments: int and double
```

在主类模板中，模板参数包必须是模板参数列表中的最后一个参数。在函数模板中，模板参数包可能出现在列表的前面，前提是以下所有参数都可以从函数参数中推导出来，或者具有默认参数：

```c++
template<typename U, typename... Ts>    // OK: can deduce U
struct valid;
// template<typename... Ts, typename U> // Error: Ts... not at the end
// struct Invalid;
 
template<typename... Ts, typename U, typename=void>
void valid(U, Ts...);    // OK: can deduce U
// void valid(Ts..., U); // Can't be used: Ts... is a non-deduced context in this position
 
valid(1.0, 1, 2, 3);     // OK: deduces U as double, Ts as {int, int, int}
```

嵌套例子

```c++
template<typename...>
struct Tuple {};
 
template<typename T1, typename T2>
struct Pair {};
 
template<class... Args1>
struct zip
{
    template<class... Args2>
    struct with
    {
        typedef Tuple<Pair<Args1, Args2>...> type;
        // Pair<Args1, Args2>... is the pack expansion
        // Pair<Args1, Args2> is the pattern
    };
};
 
typedef zip<short, int>::with<unsigned short, unsigned>::type T1;
// Pair<Args1, Args2>... expands to
// Pair<short, unsigned short>, Pair<int, unsigned int> 
// T1 is Tuple<Pair<short, unsigned short>, Pair<int, unsigned>>
 
// typedef zip<short>::with<unsigned short, unsigned>::type T2;
// error: pack expansion contains parameter packs of different lengths
```

函数参数列表 包扩展可能出现在函数调用运算符的括号内，在这种情况下，省略号左侧的最大表达式或花括号初始化列表是扩展的模式：

```c++
f(args...);              // expands to f(E1, E2, E3)
f(&args...);             // expands to f(&E1, &E2, &E3)
f(n, ++args...);         // expands to f(n, ++E1, ++E2, ++E3);
f(++args..., n);         // expands to f(++E1, ++E2, ++E3, n);
 
f(const_cast<const Args*>(&args)...);
// f(const_cast<const E1*>(&X1), const_cast<const E2*>(&X2), const_cast<const E3*>(&X3))
 
f(h(args...) + args...); // expands to 
// f(h(E1, E2, E3) + E1, h(E1, E2, E3) + E2, h(E1, E2, E3) + E3)
```

一个较为复杂的参数包的例子

```c++
#include <iostream>
 
void tprintf(const char* format) // base function
{
    std::cout << format;
}
 
template<typename T, typename... Targs>
void tprintf(const char* format, T value, Targs... Fargs) // recursive variadic function
{
    for (; *format != '\0'; format++)
    {
        if (*format == '%')
        {
            std::cout << value;
            tprintf(format + 1, Fargs...); // recursive call
            return;
        }
        std::cout << *format;
    }
}
 
int main()
{
    tprintf("% world% %\n", "Hello", '!', 123);
}
//output：Hello world! 123
```



## 示例代码

### example code1

```c++
template<typename TRet, typename... TArgs>
struct is_callable<TRet(*)(TArgs...)>{
const static bool value = true;
};
```



### example code2

```c++
    /// Construct a cpp_function from a vanilla function pointer
    template <typename Return, typename... Args, typename... Extra>
    Svar(Return (*f)(Args...), const Extra&... extra);
	template <typename Return, typename... Args, typename... Extra>
	Svar::Svar(Return (*f)(Args...), const Extra&... extra)
    :_obj(std::make_shared<SvarFunction>(f,extra...)){}
```



### example code3

```c++
/// Special internal constructor for functors, lambda functions, methods etc.
template <typename Func, typename Return, typename... Args, typename... Extra>
void SvarFunction::initialize(Func &&f, Return (*)(Args...), const Extra&... extra)
{
    // FIXME: this template used over 50% percent of binary size and slow down compile speed
    this->arg_types={SvarClass::instance<Return>(),SvarClass::instance<Args>()...};// about 15%
    std::vector<Svar> extras={extra...};
    for(Svar e:extras) process_extra(e);

    _func=[this,f](std::vector<Svar>& args)->Svar{ // about 19%
        using indices = detail::make_index_sequence<sizeof...(Args)>;
        return call_impl(f,(Return (*) (Args...)) nullptr,args,indices{});// about 19%
    };
}
```



### example code4

```c++
template <typename T>
detail::enable_if_t<std::is_pointer<T>::value,T>
Svar::castAs(){
    typedef typename std::remove_const<typename std::remove_pointer<T>::type>::type* rcptr;
    typedef typename std::remove_pointer<T>::type rpt;

    // T* -> T*
    const void* ptr=_obj->as(typeid(T));
    if(ptr) return *(T*)ptr;

    // T -> T*
    ptr=_obj->as(typeid(rpt));
    if(ptr) return (rpt*)ptr;

    // T* -> T const*
    ptr=_obj->as(typeid(rcptr));
    if(ptr) return *(rcptr*)ptr;

    // nullptr
    if(isNull()) return (T)nullptr;

    auto ret=caster<T>::from(*this);
    if(!ret.template is<T>())
        throw SvarExeption("Unable cast "+typeName()+" to "+SvarClass::Class<T>().name());
    return ret.template as<T>();// let compiler happy
}
```

### example code 5

```c++
template<typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
struct traits<Array<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> > : traits<Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> >
{
  typedef ArrayXpr XprKind;
  typedef ArrayBase<Array<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> > XprBase;
};
}
```

### example code 6

```C++
REGISTER_INITIALIZER(InitializerOpt,opt);



#define REGISTER_INITIALIZER(D,E) \
    extern "C" InitializerPtr create##E(){ return InitializerPtr(new D());}\
    class D##E##_Register{ \
    public: D##E##_Register(){\
    GSLAM::SvarWithType<funcCreateInitializer>::instance().insert(#E,create##E);\
}}D##E##_instance;



inline InitializerPtr Initializer::create(std::string desireType){
    auto& inst=GSLAM::SvarWithType<funcCreateInitializer>::instance();
    funcCreateInitializer createFunc=inst.get_var(desireType,NULL);
    if(!createFunc) return InitializerPtr();
    return createFunc();
}
```
