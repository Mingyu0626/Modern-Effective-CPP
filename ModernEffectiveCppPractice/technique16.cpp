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
        // ĳ�ð� ��ȿ���� ������ �ٵ��� ����ؼ� rootVals�� ������ �д�.
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


// atomic�� �̿��� ���� - ������
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


// mutex�� �̿��� ���� - ����
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
    double distanceFrmOrigin() const noexcept // noexcept�� �׸�14 ����
    {
        ++callCount; // ������ ����
        return std::hypot(x, y); // std::hypo�� C++11�� �� �Լ�, std::sqrt(x*x + y*y)�� �ǹ�
    }
private:
    mutable atomic<unsigned> callCount{ 0 };
    double x, y;
};



int main()
{


	return 0;
}