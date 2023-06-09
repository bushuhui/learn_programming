#include "Avar.h"
#include "PluginBase.h"

typedef std::shared_ptr<PluginBase> PluginBasePtr;

int test_plugin(void) 
{
  PluginBasePtr pa = Plugin(PluginBase)::create("PluginA");
  PluginBasePtr pb = Plugin(PluginBase)::create("PluginB");

  pa->act("hello");
  pb->act("world");
}

int main (int argc, char **argv) {

  test_plugin();
  return 0;
}