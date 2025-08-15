#include "cpp11.h"
#include "Svar.h"

int main(int argc,char** argv)
{
    svar.ParseMain(argc,argv);
    if(argc<2) {
       std::cerr<<"cpp11 [-keywords] [-stl] [-thread] [-ptr] [-others]\n";
    }

    if(svar.GetInt("keywords"))
        cpp11_keywords();

    if(svar.GetInt("stl"))
        cpp11_stl();

    if(svar.GetInt("thread"))
        cpp11_thread();

    if(svar.GetInt("ptr"))
        cpp11_shared_ptr();

    if(svar.GetInt("others"))
        cpp11_others();

    return 0;
}
