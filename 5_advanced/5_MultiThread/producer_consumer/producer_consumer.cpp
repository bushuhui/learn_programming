#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <sys/stat.h>

using namespace std;

static const int PRODUCE_NUM     = 100;
static const int STOREHOUSE_SIZE = 10;


struct StoreHouse
{
public:
    int buffer[STOREHOUSE_SIZE];
    size_t commoditynumber;

    mutex mut;                                      // 多线程读写保护-互斥体
    condition_variable buf_not_full;
    condition_variable buf_not_empty;

public:
    StoreHouse() {
        commoditynumber = 0;
    }
} gStoreHouse;

// 生成一个要素，如果队列已经满，则等待消费者线程消费一个要素之后再继续运行
void Produce(StoreHouse *store, int n)
{
    unique_lock<std::mutex> lock(store->mut);       //加锁，会自动解锁;
    
    while(store->commoditynumber==STOREHOUSE_SIZE)
    {
        cout<<"wait the store is full"<<endl;
        store->buf_not_full.wait(lock);             // 等待消费者消费一个要素
    }

    store->buffer[store->commoditynumber++]=n;

    store->buf_not_empty.notify_all();              // notify `consume` to work
}

// 消费一个要素，如果队列为空，则等待生产者生产一个要素
int  Consume(StoreHouse *store)
{
    unique_lock<std::mutex> lock(store->mut);

    while(store->commoditynumber ==0 )
    {
        cout<<"wait the store is not empty"<<endl;
        store->buf_not_empty.wait(lock);            // 等待生产者生产一个要素
    }

    int n=store->buffer[--store->commoditynumber];

    store->buf_not_full.notify_all();               // notify `producer` to work

    return n;
}

void ProduceTask()
{
    for(int i=0;i<PRODUCE_NUM;i++)
    {
        Produce(&gStoreHouse, i);
    }
}

void ConsumeTask()
{
    for(int i=0;i<PRODUCE_NUM;i++)
    {
        cout<<" the "<<Consume(&gStoreHouse)<<" is consumed"<<endl;
    }
}


int main(int argc, char *argv[])
{
    thread produced(ProduceTask);
    thread consumed(ConsumeTask);
    produced.join();
    consumed.join();

    return 0;
}
