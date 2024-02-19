#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <vector>
#include <future>
#include <queue>
#include <functional>

#include "Glog.h"


void simple_threadfunc()
{
    LOG(INFO)<<"Simple thread function.";
}

void simple_pooledfunc(int i){
    LOG(INFO)<<"Thread "<<i<<", ID:"<<std::this_thread::get_id();
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
}

class MultiReadWrite{
public:
    std::vector<int>  _vec;
    std::mutex        _mutex;
    std::atomic<bool> _shouldStop;
    std::vector<std::thread> _threads;

    MultiReadWrite(){
        _shouldStop=false;
        for(int i=0;i<2;i++)
            _threads.push_back(std::thread(&MultiReadWrite::writeThread,this));
        for(int i=0;i<2;i++)
            _threads.push_back(std::thread(&MultiReadWrite::readThread,this));
        for(int i=0;i<2;i++)
            _threads.push_back(std::thread(&MultiReadWrite::deleteThread,this));
    }
    ~MultiReadWrite(){
        _shouldStop=true;
        for(auto& t:_threads) t.join();
    }

    void writeThread(){
        for(int i=0;!_shouldStop;i++)
        {
            _mutex.lock();
            if(_vec.size()<100)
                _vec.push_back(i);
            _mutex.unlock();
            std::this_thread::sleep_for(std::chrono::microseconds(5));
        }
    }

    void readThread(){
        while(!_shouldStop)
        {
            {
                std::unique_lock<std::mutex> lock(_mutex);
                if(_vec.size())
                    LOG(INFO)<<std::this_thread::get_id()<<" get "<<_vec.back();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }

    void deleteThread(){
        while(!_shouldStop){
            {   std::unique_lock<std::mutex> lock(_mutex);
                if(_vec.size()>1)
                    _vec.pop_back();
            }
            std::this_thread::sleep_for(std::chrono::microseconds(5));
        }
    }
};

class ConditionPool
{
public:
    std::mutex               _mutex;
    std::condition_variable  _condition;
    std::vector<std::thread> _threads;
    bool                     _ready;

    ConditionPool(int thread_num=4){
        _ready=false;
        for(int i=0;i<thread_num;i++)
            _threads.push_back(std::thread(&ConditionPool::process,this));
    }

    ~ConditionPool(){
        _condition.notify_all();
        for(auto& t:_threads) t.join();
    }

    void process() {
        std::unique_lock<std::mutex> lck(_mutex);
        while (!_ready)
            _condition.wait(lck);
        LOG(INFO) << "thread " << std::this_thread::get_id();
    }

    void go() {
        std::unique_lock<std::mutex> lck(_mutex);
        _ready = true;
        _condition.notify_all();
    }
};


// A simple threadpool implementation.
class ThreadPool {
public:
    // All the threads are created upon construction.
    explicit ThreadPool(const int num_threads): stop(false) {
        CHECK_GE(num_threads, 1)
                << "The number of threads specified to the ThreadPool is insufficient.";
        for (size_t i = 0; i < num_threads; ++i) {
            workers.emplace_back([this] {
                for (;;) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this] {
                            return this->stop || !this->tasks.empty();
                        });
                        if (this->stop && this->tasks.empty()) return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    task();
                }
            });
        }
    }

    ~ThreadPool(){
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& worker : workers)
            worker.join();
    }


    // Adds a task to the threadpool.
    template <class F, class... Args>
    auto Add(F&& f, Args&& ... args)
    ->std::future<typename std::result_of<F(Args...)>::type>;

private:
    // Keep track of threads so we can join them
    std::vector<std::thread> workers;
    // The task queue
    std::queue<std::function<void()> > tasks;

    // Synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

// add new work item to the pool
template <class F, class... Args>
auto ThreadPool::Add(F&& f, Args&& ... args)
->std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()> >(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        CHECK(!stop) << "The ThreadPool object has been destroyed! Cannot add more "
                        "tasks to the ThreadPool!";

        tasks.emplace([task]() {
            (*task)();
        });
    }
    condition.notify_one();
    return res;
}

int cpp11_thread()
{
    // simple thread call
    std::thread thread1(simple_threadfunc);
    thread1.join();

    // simple thread with lamda func
    std::vector<int> vec(4,10);
    std::thread thread2([&vec]{for(auto i:vec) vec[0]+=i;});
    LOG(INFO)<<vec[0];
    thread2.join();

    // simple thread pool
    std::vector<std::thread> threads(4);
    for(int i=0;i<threads.size();i++)
        threads[i]=std::thread(simple_pooledfunc,i);

    for(auto& thread:threads) thread.join();

    // simple multi readwrite, mutex
    {
        MultiReadWrite mutexTest;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // simple condition usage
    ConditionPool conditionPool(4);
    conditionPool.go();

    // thread pool with future return
    ThreadPool pool(4);
    std::vector<int> vec1(4,10);
    auto result=pool.Add([vec1]{int sum=0;for(auto i:vec1) sum+=i;return sum;});
    result.wait();

    LOG(INFO)<<"sum is "<<result.get();
}
