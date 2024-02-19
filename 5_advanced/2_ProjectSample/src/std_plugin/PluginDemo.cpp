
#include "PluginDef.h"


int test_plugin(void)
{
    PluginPtr pa = PluginBase::create("PluginA");
    PluginPtr pb = PluginBase::create("PluginB");

    pa->act("hello");
    pb->act("world");

    return 0;
}

int main(int argc, char *argv[])
{
    test_plugin();

    return 0;
}

