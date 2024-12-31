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

// std::condition_variable�� ����� �ڵ�
std::condition_variable cv;
std::mutex m;
// ���� ����
{
    cv.notify_one();
}
// ���� ����
{
    ...
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk);
        ...
    }
    ...
}



// bool flag�� condition_variable�� �Բ� ����� �ڵ�
std::condition_variable cv;
std::mutex m;
bool flag(false);
// ���� ����
{
    ...
    {
        std::lock_guard<std::mutex> g(m);
        flag = true;
    }
}
// ���� ����
{
    ...
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [] { return flag; });
        ...
    }
    ...
}



// std::promise�� ����ϴ� ���
std::promise<void> p; // ��� ä�ο��� ����� promise ��ü

class ThreadRAII
{
public:
    enum class DtorAction { join, detach };

    ThreadRAII(std::thread&& t, DtorAction a) // �Ҹ��ڿ���, t�� ���� ���� a�� ����
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

// ���� ����
void react();

// ���� ����
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

// ���� ���� ���� ������ ����
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