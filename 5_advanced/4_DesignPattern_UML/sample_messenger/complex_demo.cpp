#include <stdlib.h>
#include <math.h>

#include "Messenger.h"
#include "Svar.h"

///This file is a demo code for messenger communication cross threads using class member function

using namespace std;
using namespace GSLAM;


//class A and B is an example of class communication via messenger
class DemoA
{
public:
    DemoA()
    {
        //get topic string predifined in Svar
        string topicName = svar.GetString("DemoA_do1", "printString");
        string topicName2 = svar.GetString("DemoA_do2", "calculate");
        //set queue size, val > 1 will opreate in different thread
        int queueSize = 1;

        //define subcriber
        //subscribing member function pattern should be (topicName, queueSize, memeberFunctionPtr, classInstancePtr/classPtr)
        subAct = messenger.subscribe(topicName, queueSize, &DemoA::doAct, this);
        subAct2 = messenger.subscribe(topicName2, 1, &DemoA::doAct2, this);
    }

    ~DemoA(){}

    //member function called in subscriber, parameter should be const reference
    void doAct(const string& msg)
    {
        cout << "A is printing Message: \n" << msg << endl;


        //sending feedback by publishing a message
        string topicFed1 = svar.GetString("feedBack1", "A_doPrintString_fed");
        int queueSize = 1;
        //create a publisher to send feedback
        auto pubFeedBack = messenger.advertise<int>(topicFed1, queueSize);

        int feedMsg = 0;
        pubFeedBack.publish(feedMsg);
    }

    void doAct2(const int& msg)
    {
        int ans = pow(msg, 5);
        cout << "A is calculating, answer is :\n" << ans << endl;

        //sending feedback
        string topicFed2 = svar.GetString("feedBack2", "A_doCalculate_fed");
        int queueSize = 1;
        auto pubFeedBack = messenger.advertise<int>(topicFed2, queueSize);
        int feedMsg = ans;
        pubFeedBack.publish(feedMsg);
    }

public:
    //create member variant of subscriber to receive msg
    Subscriber      subAct;
    Subscriber      subAct2;
};

class DemoB
{
public:
    DemoB()
    {
        //definition of subscribers
        string topicFeed1 = svar.GetString("feedBack1", "A_doPrintString_fed");
        string topicFeed2 = svar.GetString("feedBack2", "A_doCalculate_fed");
        int queueSize = 1;

        subFeed1 = messenger.subscribe(topicFeed1, queueSize, &DemoB::recvFeed1, this);
        subFeed2 = messenger.subscribe(topicFeed2, queueSize, &DemoB::recvFeed2, this);
    }

    ~DemoB(){}

    void askAct1(string msg)
    {
        string topicAct1 = svar.GetString("DemoA_do1", "printString");
        int queueSize = 1;
        auto pubAskAct1 = messenger.advertise<string>(topicAct1, queueSize);
        
        cout << "B is asking A to do act " << topicAct1 << endl;
        pubAskAct1.publish(msg);
    }

    void askAct2(int msg)
    {
        string topicAct2 = svar.GetString("DemoA_do2", "calculate");
        int queueSize = 1;
        auto pubAskAct2 = messenger.advertise<string>(topicAct2, queueSize);
        
        cout << "B is asking A to do act " << topicAct2 << "value of input is: " << msg <<  endl;
        pubAskAct2.publish(msg);
    }

    void recvFeed1(const int& msg)
    {
        if( msg == 0 )
        {
            cout << "B received feedback from A, printString operation success!\n";
        }
        else
        {
            cout << "B received feedback from A, printString operation falied, error msg: " << msg << endl;
        }
    }
    
    void recvFeed2(const int& msg)
    {
        cout << "B received feedback from A, calculate operation success!, answer is: " << msg << endl;
    }

public:
    //member variant to receive feedback from A
    Subscriber      subFeed1;
    Subscriber      subFeed2;
};


int main (int argc, char** argv)
{
    svar.ParseMain(argc, argv);

    //Do communications between class obejcts
    DemoA instanceA;
    DemoB instanceB;

    //do act1: printString
    string msgStr = "Good luck! Have fun!";
    instanceB.askAct1(msgStr);

    //do act2: calculate
    int msgInt = 7;
    instanceB.askAct2(msgInt);

    return 0;
}
