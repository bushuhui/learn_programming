/*
 * References:
 *  doc/references/c++/memory_leakage.md
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <iostream>

#include <vector>
#include <deque>
#include <map>
#include <algorithm>
#include <thread>

#include "GSLAM/core/Svar.h"
#include "GSLAM/core/SPtr.h"
#include "GSLAM/core/Timer.h"

#include "utils_debug.h"

#include "utils.h"
#include "OfflineFIFO.h"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class TestOfflineFifo
{
public:
    TestOfflineFifo()
    {
        _shouldStop = false;

        msgQueue = SPtr<OfflineFifo>(new OfflineFifo("tem/ob", 200));

        thread_send = std::thread(&TestOfflineFifo::thread_send_message, this);
        thread_recv = std::thread(&TestOfflineFifo::thread_recv_message, this);

        msgNum = 1000;
    }

    virtual ~TestOfflineFifo()
    {
        _shouldStop = true;
        thread_send.join();
        thread_recv.join();
    }

    void thread_send_message(void)
    {
        GSLAM::Rate r(30);
        int idx = 0;

        while( !_shouldStop )
        {
            BuffType m(new std::vector<uint8_t>(10*1024*1024));
            msgQueue->push(m);

            printf("[%8d] send msg (%8d)\n", idx++, m->size());

            r.sleep();

            {
                int n=8;
                int *p = (int*) malloc(n*sizeof(int));
                for(int j=0; j<n; j++) p[j] = j%256;
            }
        }
    }

    void thread_recv_message(void)
    {
        GSLAM::Rate r(20);
        int idx = 0;

        while( !_shouldStop )
        {
            BuffType m = msgQueue->pop();
            if( m )
            {
                printf("[%8d] recv msg (%8d)\n", idx++, m->size());
            }

            r.sleep();
        }
    }

protected:
    int                     msgNum;

    std::thread             thread_send, thread_recv;
    SPtr<OfflineFifo>       msgQueue;
    mutable bool            _shouldStop;
};

int test_offline_fifo(void)
{
    {
        GSLAM::Rate r(1);
        TestOfflineFifo t;

        printf(">>>>> begin OfflineFIFO test\n");

        int n=10;
        for(int i=0; i<n; i++) r.sleep();

        for(int i=0; i<10; i++)
        {
            int n=32;
            int *p = (int*) malloc(n*sizeof(int));
            for(int j=0; j<n; j++) p[j] = j%256;
        }
    }

    {
        GSLAM::Rate r(1);

        printf(">>>>> stop OfflineFIFO test\n");

        int n=10;
        for(int i=0; i<n; i++) r.sleep();

        for(int i=0; i<10; i++)
        {
            int n=16;
            int *p = (int*) malloc(n*sizeof(int));
            for(int j=0; j<n; j++) p[j] = j%256;
        }
    }
}

int test_segmentfault()
{
    int *p = (int*)0x00023;
    *p = 10;

    return 0;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    dbg_stacktrace_setup();

    #define DEF_TEST(f) if( act == #f ) return f()

    svar.ParseMain(argc, argv);
    std::string act = svar.GetString("Act", "test_offline_fifo");

    DEF_TEST(test_offline_fifo);
    DEF_TEST(test_segmentfault);
}
