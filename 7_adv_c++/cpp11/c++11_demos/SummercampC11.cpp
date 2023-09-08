#include "SummercampC11.h"


class NullTest
{
public:
    void TestWork(int index)
    {
        std::cout << "TestWork 1" << std::endl;
    }
    void TestWork(int * index)
    {
        std::cout << "TestWork 2" << std::endl;
    }
};

void threadfun1()
{
    std::cout << "threadfun1 - 1" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "threadfun1 - 2" << std::endl;
}

void threadfun2(int iParam, std::string sParam)
{
    std::cout << "threadfun2 - 1" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "threadfun2 - 2" << std::endl;
}

/* 下面这个等于赋值在windows下可以， 但是在Ubuntu下测试是不行的 */
#if 0
std::atomic_bool bIsReady = false;
std::atomic_int iCount = 100;

//std::atomic_bool bIsReady(false);
//std::atomic_int iCount(100);
void threadfun3()
{
    if (!bIsReady) {
        std::this_thread::yield();
    }
    while (iCount > 0)
    {
        printf("iCount:%d\r\n", iCount--);
    }
}
#endif

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
    std::unique_lock<std::mutex> lck(mtx);
    /* // 调用wait会挂起当前线程, 并释放锁 */
    while (!ready)
        cv.wait(lck);
    std::cout << "thread " << id << '\n';
}

void go() {
    std::unique_lock<std::mutex> lck(mtx);
    ready = true;
    /* // 唤醒所有的挂起线程. */
    cv.notify_all();
}

class SharedPtrTest
{
public:
    SharedPtrTest()
    {
        std::cout << "SharedPtrTest()" << std::endl;
    }
    ~SharedPtrTest()
    {
        std::cout << "~SharedPtrTest()" << std::endl;
    }
};

class WeakPtrTestB;
class WeakPtrTestA
{
public:
    WeakPtrTestA()
    {
        std::cout << "WeakPtrTestA()" << std::endl;
    }
    void ReferTestB(std::shared_ptr<WeakPtrTestB> test_ptr)
    {
        m_TestB_Ptr = test_ptr;
    }
    ~WeakPtrTestA()
    {
        std::cout << "~WeakPtrTestA()" << std::endl;
    }
private:
    /* TestB的智能指针 */
    std::shared_ptr<WeakPtrTestB> m_TestB_Ptr;
};

class WeakPtrTestB
{
public:
    WeakPtrTestB()
    {
        std::cout << "WeakPtrTestB()" << std::endl;
    }

    void ReferTestB(std::shared_ptr<WeakPtrTestA> test_ptr)
    {
        m_TestA_Ptr = test_ptr;
    }
    ~WeakPtrTestB()
    {
        std::cout << "~WeakPtrTestB()" << std::endl;
    }
    /* //TestA的智能指针 */
    std::weak_ptr<WeakPtrTestA> m_TestA_Ptr;
    /* //TestA的智能指针 */
//    std::shared_ptr<WeakPtrTestA> m_TestA_Ptr;
};


int main()
{
    auto index = 10;
    auto str = "abc";
    std::cout << "index:" << index << std::endl;
    std::cout << "str:" << str << std::endl;
    std::cout << "size: " << sizeof(index) << std::endl;

/*    // 花括号初始化 */
    vector<int> nums = {1, 2, 3};
    for(auto num: nums){
        cout << num << endl;
    }
    for(auto &num: nums){
        num = 1;
    }
    PrintVector(nums);
/* //    下面这个是错误的 */
//    for(auto iter: nums.begin()){
//        cout << *iter << endl;
//    }
    for(auto iter = nums.begin(); iter != nums.end(); ++iter){
        cout << *iter << endl;
    }



    NullTest test;
/*//    调用错误
//    既能匹配int, 又能匹配int *
      我在windows下这个NULL是可以的，但是在Ubuntu的情况下是不能调用的*/
    //test.TestWork(NULL);
    test.TestWork(nullptr);



    std::array<int, 4> arrayDemo = { 1,2,3,4 };
    std::cout << "arrayDemo:" << std::endl;
    for (auto itor : arrayDemo)
    {
        std::cout << itor << std::endl;
    }
    int arrayDemoSize = sizeof(arrayDemo);
    std::cout << "arrayDemo size:" << arrayDemoSize << std::endl;

    clock_t time_start=clock();
    for(int i = 0; i < 10000000; ++i){
        array<int, 4> arrayDemo = {1, 2, 3, 4};
        for(int j = 0; j < 4; ++j){
            arrayDemo[j] = arrayDemo[j] + 1;
        }
    }
    clock_t time_end=clock();
    cout<<"time use:"<<1000*(time_end-time_start)/(double)CLOCKS_PER_SEC<<"ms"<<endl;

    time_start=clock();
    for(int i = 0; i < 10000000; ++i){
        vector<int> vectorDemo(4, 0);
        for(int j = 0; j < 4; ++j){
            vectorDemo[j] = vectorDemo[j] + 1;
        }
    }
    time_end=clock();
    cout<<"time use:"<<1000*(time_end-time_start)/(double)CLOCKS_PER_SEC<<"ms"<<endl;




    std::forward_list<int> numbers = {1,2,3,4,5,4,4};
    std::cout << "numbers:" << std::endl;
    for (auto number : numbers)
    {
        std::cout << number << std::endl;
    }
    numbers.remove(1);
    std::cout << "numbers after remove:" << std::endl;
    for (auto number : numbers)
    {
        std::cout << number << std::endl;
    }



    std::unordered_map<std::string, std::string> mymap ={
        { "house","maison" },
        { "apple","pomme" },
        { "tree","arbre" },
        { "book","livre" },
        { "door","porte" },
        { "grapefruit","pamplemousse" }
    };
    size_t n = mymap.bucket_count();
    std::cout << "mymap has " << n << " buckets.\n";
    for (unsigned i = 0; i<n; ++i)
    {
        std::cout << "bucket #" << i << " contains: ";
        for (auto it = mymap.begin(i); it != mymap.end(i); ++it)
            std::cout << "[" << it->first << ":" << it->second << "] ";
        std::cout << "\n";
    }

    map<int, int> m1;
    unordered_map<int, int> m2;
    int times = 7;

    time_start=clock();
    for(int i = 0; i < 10000000; ++i){
        for(int j = 0; j < times; ++j){
            m1[j] = j;
        }
    }
    time_end=clock();
    cout<<"map time use:"<<1000*(time_end-time_start)/(double)CLOCKS_PER_SEC<<"ms"<<endl;

    time_start=clock();
    for(int i = 0; i < 10000000; ++i){
        for(int j = 0; j < times; ++j){
            m2[j] = j;
        }
    }
    time_end=clock();
    cout<<"unordered_map time use:"<<1000*(time_end-time_start)/(double)CLOCKS_PER_SEC<<"ms"<<endl;

    unordered_map<string, int> m3;
    vector<string> strs = {"1", "2", "3","4","5","6","7"};
    time_start=clock();
    for(int i = 0; i < 10000000; ++i){
        for(int j = 0; j < times; ++j){
            m3[strs[j]] = j;
        }
    }
    time_end=clock();
    cout<<"unordered_map time use:"<<1000*(time_end-time_start)/(double)CLOCKS_PER_SEC<<"ms"<<endl;

    map<string, int> m4;
    time_start=clock();
    for(int i = 0; i < 10000000; ++i){
        for(int j = 0; j < times; ++j){
            m4[strs[j]] = j;
        }
    }
    time_end=clock();
    cout<<"map time use:"<<1000*(time_end-time_start)/(double)CLOCKS_PER_SEC<<"ms"<<endl;




    std::unordered_set<int> unorder_set;
    unorder_set.insert(7);
    unorder_set.insert(5);
    unorder_set.insert(3);
    unorder_set.insert(4);
    unorder_set.insert(6);
    std::cout << "unorder_set:" << std::endl;
    for (auto itor : unorder_set)
    {
        std::cout << itor << std::endl;
    }

    std::set<int> set;
    set.insert(7);
    set.insert(5);
    set.insert(3);
    set.insert(4);
    set.insert(6);
    std::cout << "set:" << std::endl;
    for (auto itor : set)
    {
        std::cout << itor << std::endl;
    }



    std::thread t1(threadfun1);
    std::thread t2(threadfun2, 10, "abc");
    t1.join();
    std::cout << "join" << std::endl;
    t2.detach();
    std::cout << "detach" << std::endl;



    std::list<std::thread> lstThread;
    for (int i = 0; i < 10; ++i)
    {
        lstThread.push_back(std::thread(threadfun1));
    }
    for (auto& th : lstThread)
    {
        th.join();
    }



    std::thread threads[10];
    // spawn 10 threads:
    for (int i = 0; i<10; ++i)
        threads[i] = std::thread(print_id, i);

    std::cout << "10 threads ready to race...\n";
    go();

    for (auto& th : threads) th.join();



    std::shared_ptr<SharedPtrTest> p1 = std::make_shared<SharedPtrTest>();
    std::cout << "1 ref:" << p1.use_count() << std::endl;
    {
        std::shared_ptr<SharedPtrTest> p2 = p1;
        std::cout << "2 ref:" << p1.use_count() << std::endl;
    }
    std::cout << "3 ref:" << p1.use_count() << std::endl;




    std::shared_ptr<WeakPtrTestA> ptr_a = std::make_shared<WeakPtrTestA>();
    std::shared_ptr<WeakPtrTestB> ptr_b = std::make_shared<WeakPtrTestB>();
    ptr_a->ReferTestB(ptr_b);
    ptr_b->ReferTestB(ptr_a);



    FunctionTest functionTest;
    functionTest.Add(add, 1, 2);
    TestAdd testAdd;
    /* 使用了bind可以传入类中的成员函数 */
    /* std::bind第一个参数为对象函数指针，表示函数相对于类的首地址的偏移量 */
    /* std::placeholders::_1和std::placeholders::_2为参数占位符，表示std::bind封装的可执行对象可以接受两个参数。 */
    functionTest.Add(std::bind(&TestAdd::Add, testAdd, std::placeholders::_1, std::placeholders::_2), 1, 2);


/*    []：中括号用于控制main函数与内，lamda表达式之前的变量在lambda表达式中的访问形式；
//    （int a,int b）：为函数的形参
//    ->int：lambda表达式函数的返回值定义
//    {}:大括号内为lamda表达式的函数体。 */
    int a = 1;
    auto add= [a](int b, int c)->int{
        /* 下面这个a=0会报错，因为无法进行改变 */
//        a = 0;
        return b + c;
    };
    int ret3 = add(1,2);
    std::cout << "ret3:" << ret3 << ", a: " << a << std::endl;


    auto add2 = [&a](int b, int c){
        a = 0;
        return b + c;
    };
    int ret4 = add2(1,2);
    std::cout << "ret4:" << ret4 << ", a: " << a << std::endl;

    vector<int> lambdaNums = {2, 3, 1};
    sort(lambdaNums.begin(), lambdaNums.end(), [](const int &a, const int &b){
        return a < b;
    });
    PrintVector(lambdaNums);
    sort(lambdaNums.begin(), lambdaNums.end(), [](const int &a, const int &b){
        return a > b;
    });
    PrintVector(lambdaNums);
}
