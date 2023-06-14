#include "PluginDef.h"


int test_plugin(void)
{
    PluginPtr pa = PluginBase::create("PluginA");
    PluginPtr pb = PluginBase::create("PluginB");
    PluginPtr pc = PluginBase::create("PluginB");

    pa->act("hello");
    pb->act("world");
    cout<<"the pb address is "<<&pb<<endl;
    pc->act("world");
    cout<<"the pb address is "<<&pc<<endl;
    return 0;
}

int main(int argc, char *argv[])
{
    cout<<"begin main "<<endl;
    test_plugin();
    return 0;
}
