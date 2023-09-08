#include <iostream>
#include <string>

using namespace std;

struct Say{
  Say(std::string str):str(str){}
  
  void say(){
    std::cout<<str<<std::endl;
  }  

  std::string str;
};

int say(int a){std::cout<<a<<std::endl;}
void say(double a){std::cout<<a<<std::endl;}


//extern "C" void _Z3sayd(){}

int main()
{
   Say h("Hello World");
   h.say();

   say(1);
   say(1.2);
   return 0;
}
