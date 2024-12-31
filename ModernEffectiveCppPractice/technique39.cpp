#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
#include <thread>
#include <future>
#include <mutex>
#include <cassert>
#include <functional>
#include <new>
#include <utility>

using namespace std;

class Widget {};

// std::condition_variable을 사용한 코드
std::condition_variable cv;
std::mutex m;
// 검출 과제
{
    cv.notify_one();
}
// 반응 과제
{
    ...
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk);
        ...
    }
    ...
}



// bool flag와 condition_variable을 함께 사용한 코드
std::condition_variable cv;
std::mutex m;
bool flag(false);
// 검출 과제
{
    ...
    {
        std::lock_guard<std::mutex> g(m);
        flag = true;
    }
}
// 반응 과제
{
    ...
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [] { return flag; });
        ...
    }
    ...
}



// std::promise를 사용하는 방법
std::promise<void> p; // 통신 채널에서 사용할 promise 객체

class ThreadRAII
{
public:
    enum class DtorAction { join, detach };

    ThreadRAII(std::thread&& t, DtorAction a) // 소멸자에서, t에 대해 동작 a를 수행
        : action(a), t(std::move(t)) {}

    ~ThreadRAII()
    {
        if (t.joinable())
        {
            if (action == DtorAction::join)
            {
                t.join();
            }
            else
            {
                t.detach();
            }
        }
    }

    ThreadRAII(ThreadRAII&&) = default;
    ThreadRAII& operator=(ThreadRAII&&) = default;

    std::thread& get() { return t; }

private:
    DtorAction action;
    std::thread t;
};

// 반응 과제
void react();

// 검출 과제
void detect()
{
    ThreadRAII tr(
        std::thread([]
            {
                p.get_future().wait();
                react();
            }),
        ThreadRAII::DtorAction::join
    );
    p.set_value();
    
}

// 여러 개의 반응 과제에 통지
std::promise<void> p;
void detect()
{
    auto sf = p.get_future().share();

    std::vector<std::thread> vt;

    for (int i = 0; i < threadsToRun; ++i) {

        vt.emplace_back([sf] { sf.wait();
        react(); });
    }

    p.set_value();

    for (auto& t : vt) 
    {
        t.join();
    }
}


int main()
{


	return 0;
}