#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
#include <thread>
#include <mutex>
#include <cassert>
#include <functional>
#include <new>
#include <utility>

using namespace std;

class Polynomial 
{
public:
    using RootsType = std::vector<double>;

    RootsType roots(void) const
    {
        lock_guard<mutex> g(m);
        // 캐시가 유효하지 않으면 근들을 계산해서 rootVals에 저장해 둔다.
        if (!rootsAreValid) 
        {
            rootsAreValid = true;
        }

        return rootVals;
    }

private:
    mutable mutex m;
    mutable bool rootsAreValid{ false };
    mutable RootsType rootVals{};
};


// atomic을 이용한 구현 - 부적절
class Widget 
{
public:
    int magicValue() const
    {
        if (cacheValid) return cachedValue;
        else
        {
            auto val1 = expensiveComputation1();
            auto val2 = expensiveComputation2();
            cachedValue = val1 + val2;
            cachedValue = true;
            return cachedValue;
        }
    }
private:
    mutable std::atomic<bool> cacheValid{ false };
    mutable std::atomic<int> cachedValue;
};


// mutex를 이용한 구현 - 적절
class Widget
{
public:
    int magicValue() const
    {
        lock_guard<mutex> guard(m);
        if (cacheValid) return cachedValue;
        else
        {
            auto val1 = expensiveComputation1();
            auto val2 = expensiveComputation2();
            cachedValue = val1 + val2;
            cachedValue = true;
            return cachedValue;
        }
    }
private:
    mutable mutex m;
    mutable bool cacheValid{ false };
    mutable int cachedValue;
};



class Point
{
public:
    double distanceFrmOrigin() const noexcept // noexcept는 항목14 참고
    {
        ++callCount; // 원자적 증가
        return std::hypot(x, y); // std::hypo는 C++11의 새 함수, std::sqrt(x*x + y*y)를 의미
    }
private:
    mutable atomic<unsigned> callCount{ 0 };
    double x, y;
};



int main()
{


	return 0;
}