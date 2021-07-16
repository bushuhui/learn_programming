#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

using namespace std;

static const int ITEM_TOTAL_SIZE=100;
static const int STOREHOUSE_SIZE=10;


struct STOREHOUSE
{
    int buffer[STOREHOUSE_SIZE];
    size_t commoditynumber;
    size_t index;
    mutex mut;    //互斥体;
    condition_variable buf_not_full;
    condition_variable buf_not_empty;
} gstorehouse;

void Produce(STOREHOUSE *store,int n)
{
    unique_lock<std::mutex> lock(store->mut);    //加锁，会自动解锁;
    while(store->commoditynumber==STOREHOUSE_SIZE)
    {
        cout<<"wait the store is not full"<<endl;
        store->buf_not_full.wait(lock);          //解锁阻塞当前线程
    }
    store->buffer[store->commoditynumber++]=n;

    if(store->commoditynumber==STOREHOUSE_SIZE)
    {

        cout<<"the store is not empty"<<endl;
        store->buf_not_empty.notify_all();        //通知另一个线程加锁运行
    }
}

int  Consume(STOREHOUSE *store)
{
    unique_lock<std::mutex> lock(store->mut);
    while(store->commoditynumber==0)
    {
        cout<<"wait the store is not empty"<<endl;
        store->buf_not_empty.wait(lock);
    }

    int n=store->buffer[--store->commoditynumber];

    if(store->commoditynumber==0)
    {
        store->buf_not_full.notify_all();
    }

    return n;
}

void Producetask()
{
    for(int i=0;i<ITEM_TOTAL_SIZE;i++)
    {
        Produce(&gstorehouse,i);
    }
}

void Consumetask()
{
    for(int i=0;i<ITEM_TOTAL_SIZE;i++)
    {
        cout<<" the "<<Consume(&gstorehouse)<<" is consumed"<<endl;
    }
}

void storeinit(STOREHOUSE *store)
{
    store->commoditynumber=0;
    store->index=0;
}

int main(int argc, char *argv[])
{
    storeinit(&gstorehouse);
    thread produced(Producetask);
    thread consumed(Consumetask);
    produced.join();
    consumed.join();
    return 0;
}
