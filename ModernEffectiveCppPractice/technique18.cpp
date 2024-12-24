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

class Widget {};

class Investment
{
};

class Stock : public Investment
{
};

class Bond : public Investment
{
};

class RealEstate : public Investment
{
};



// C++11 버전
// 주어진 인수들로 생성한 객체를 가리키는 std::unique_ptr를 돌려줌
template <typename... Ts>
std::unique_ptr<Investment> makeInvestment(Ts&&... params);

auto delInvmt = [](Investment* pInvestment) // 커스텀 삭제자
    {
        makeLogEntry(pInvestment);
        delete pInvestment;
    };

template<typename... Ts>
unique_ptr<Investment, decltype(delInvmt)>
makeInvestment(Ts&&... params)
{
    std::unique_ptr<Investment, decltype(delInvmt)>
        pInv(nullptr, delInvmt);

    if ( /* Stock 객체를 생성해야 하는 경우 */)
    {
        pInv.reset(new Stock(std::forward<Ts>(params)...));
    }
    else if ( /* Bond 객체를 생성해야 하는 경우 */)
    {
        pInv.reset(new Bond(std::forward<Ts>(params)...));
    }
    else if ( /* RealEstate 객체를 생성해야 하는 경우 */)
    {
        pInv.reset(new RealEstate(std::forward<Ts>(params)...));
    }

    return pInv;
}



// 함수 반환 타입 추론을 지원하는 C++14의 버전
template <typename... Ts>
auto makeInvestment(Ts&&... params)
{
    auto delInvmt = [](Investment* pInvestment) // 이제는 makeInvestment의 내부에서 삭제자를 정의
        {
            makeLogEntry(pInvestment);
            delete pInvestment;
        };

    std::unique_ptr<Investment, decltype(delInvmt)> pInv(nullptr, delInvmt);

    if (...)
    {
        pInv.reset(new Stock(std::forward<Ts>(params)...));
    }
    else if (...)
    {
        pInv.reset(new Bond(std::forward<Ts>(params)...));
    }
    else if (...)
    {
        pInv.reset(new RealEstate(std::forward<Ts>(params)...));
    }

    return pInv;
}



auto delInvmt1 = [](Investment* pInvestment) // 상태 없는 람다 형태의 삭제자
    {
        makeLogEntry(pInvestment);
        delete pInvestment;
    };

template<typename... Ts> // 반환 타입은 Investment*와 같은 크기
std::unique_ptr<Investment, decltype(delInvmt1)> makeInvestment(Ts&&... args);

void delInvmt2(Investment* pInvestment) // 함수 형태의 삭제자
{
    makeLogEntry(pInvestment);
    delete pInvestment;
};

template<typename... Ts> // 반환 타입의 크기는 Investment*의 크기에 적어도 함수 포인터의 크기를 더한 것임!
std::unique_ptr<Investment, void (*)(Investment*)> makeInvestment(Ts&&... params);

int main()
{


	return 0;
}