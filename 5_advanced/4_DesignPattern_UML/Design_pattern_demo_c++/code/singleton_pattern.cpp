//
// Created by likun on 5/28/23.
//

#include <iostream>
#include <mutex>

using namespace std;
std::mutex mt;

class president{
private:
    static president *instance;
    president() {}
public:
    static president *getInstance();
    void getName();
};

president* president::instance = new president();

president* president::getInstance() {
    mt.lock();
    if(instance == NULL){
        instance = new president();
    }else{
        cout<<" the president is exit !"<<endl;
    }
    mt.unlock();
    return instance;
}

void president::getName() {
    cout<<" there is president !"<<endl;
}

int main(int argc, char** argv)
{
    president* p1 = president::getInstance();
    p1->getName();
    president* p2 = president::getInstance();
    p2->getName();

    if(p1 == p2){
        cout<<"they are same one "<<endl;
    }else{
        cout<<" they are not same one "<<endl;
    }
}