
#include <stdio.h>
#include "Svar.h"


int do_print(void)
{
    // 如果程序其他部分没有设置 `nprint`值，则会使用3作为其数值
    int nprint = svar.GetInt("nprint", 3);
    for(int i=0; i<nprint; i++) {
        printf("Hello\n");
    }

    return 0;
}

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
    svar.GetInt("nprint") = 9;
    do_print();


    return 0;
}

