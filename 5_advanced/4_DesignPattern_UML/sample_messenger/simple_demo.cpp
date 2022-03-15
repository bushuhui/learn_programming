#include <stdlib.h>

#include "Svar.h"
#include "Messenger.h"

///This file is a simple demo for messenger communication using normal callback function

using namespace std;
using namespace GSLAM;




//callback function to be called in subscriber
void callBackFunc(string msg)
{
    cout << "Normal function is printing message: \n" << msg << endl;
}


int main(int argc, char** argv)
{
    svar.ParseMain(argc, argv);
    //Do communications simply

    //define topic
    string topicSimple = svar.GetString("ActSimple", "printMsg");
    int queueSize = 0;

    //create subscriber
    auto subSimple = messenger.subscribe(topicSimple, queueSize, callBackFunc);

    //create publisher
    auto pubSimple = messenger.advertise<string>(topicSimple, queueSize);

    //publish message
    string simpleMsg = "This is a simple msg sent in main funciton.";
    pubSimple.publish(simpleMsg);

    return 0;
}
