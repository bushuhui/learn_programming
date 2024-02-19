
#include "Svar.h"
#include "Messenger.h"
#include "user_data.h"
#include "PluginDef.h"

#include <iostream>
#include <vector>
#include <string>


using namespace std;
using namespace GSLAM;


///////////////////////////////////////////////////////////////////////////////
/// svar demo
///////////////////////////////////////////////////////////////////////////////

int do_print(void)
{
    // 如果程序其他部分没有设置 `nprint`值，则会使用3作为其数值
    int nprint = svar.GetInt("nprint", 3);
    for(int i=0; i<nprint; i++) {
        printf("Hello\n");
    }

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
/// messenger demo
///////////////////////////////////////////////////////////////////////////////

//callback function to be called in subscriber
void callBackFunc(string msg)
{
    cout << "Normal function is printing message: \n" << msg << endl;
}

int test_messenger(void)
{
    //define topic
    string topicSimple = svar.GetString("ActSimple", "printMsg");
    int queueSize = 0;

    //create subscriber
    auto subSimple = messenger.subscribe(topicSimple, callBackFunc, queueSize);

    //create publisher
    auto pubSimple = messenger.advertise<string>(topicSimple, queueSize);

    //publish message
    string simpleMsg = "This is a simple msg sent in main funciton.";
    pubSimple.publish(simpleMsg);

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
/// std plugin demo
///////////////////////////////////////////////////////////////////////////////

int test_std_plugin(void)
{
    PluginPtr pa = PluginBase::create("PluginA");
    PluginPtr pb = PluginBase::create("PluginB");

    pa->act("hello");
    pb->act("world");

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
/// svar plugin demo
///////////////////////////////////////////////////////////////////////////////

int test_svar_plugin(void)
{
    // test simple function
    sv::Svar a = svar.import("a");  // import 插件 a
    sv::Svar b = svar.import("b");  // import 插件 a
    
    std::cout << a["add"](1,2) << std::endl;    // 调用基本函数 `add`
    std::cout << b["add"](3,4) << std::endl;    // 调用基本函数 `add`

    // test complex arguments (user defined data)
    std::vector<UserData> list1 = { UserData("Jack", 1), UserData("Tom", 2)};
    a["list"](list1);           // 调用复杂函数 `list`
    b["list"](list1);           // 调用复杂函数 `list`
    
    return 0;
}


///////////////////////////////////////////////////////////////////////////////
/// main
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    // 通过`ParseMain`解析命令行参数，svar会自动解析当前目录下的 `Default.json`文件
    svar.ParseMain(argc, argv);
    
    // 从配置文件获取参数信息
    //  1. 下面的示例中，如果变量不存在，则返回默认值，例如10
    //  2. 参数的优先级是命令行，配置文件，如果都有的情况下，则命令行的设置优先
    int num = svar.GetInt("num", 10);
    std::string act = svar.GetString("act", "print");
    printf("num = %d\n", num);
    printf("act = %s\n", act.c_str());

    // svar可以看做是个全局的变量容器，可以在函数、类直接传递参数，这样不用定义变量，包含头文件
    do_print();

    // 测试 Messenger
    test_messenger();

    // 测试插件
    test_std_plugin();
    test_svar_plugin();

    return 0;
}
