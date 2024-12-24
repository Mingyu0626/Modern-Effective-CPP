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



// C++11 ����
// �־��� �μ���� ������ ��ü�� ����Ű�� std::unique_ptr�� ������
template <typename... Ts>
std::unique_ptr<Investment> makeInvestment(Ts&&... params);

auto delInvmt = [](Investment* pInvestment) // Ŀ���� ������
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

    if ( /* Stock ��ü�� �����ؾ� �ϴ� ��� */)
    {
        pInv.reset(new Stock(std::forward<Ts>(params)...));
    }
    else if ( /* Bond ��ü�� �����ؾ� �ϴ� ��� */)
    {
        pInv.reset(new Bond(std::forward<Ts>(params)...));
    }
    else if ( /* RealEstate ��ü�� �����ؾ� �ϴ� ��� */)
    {
        pInv.reset(new RealEstate(std::forward<Ts>(params)...));
    }

    return pInv;
}



// �Լ� ��ȯ Ÿ�� �߷��� �����ϴ� C++14�� ����
template <typename... Ts>
auto makeInvestment(Ts&&... params)
{
    auto delInvmt = [](Investment* pInvestment) // ������ makeInvestment�� ���ο��� �����ڸ� ����
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



auto delInvmt1 = [](Investment* pInvestment) // ���� ���� ���� ������ ������
    {
        makeLogEntry(pInvestment);
        delete pInvestment;
    };

template<typename... Ts> // ��ȯ Ÿ���� Investment*�� ���� ũ��
std::unique_ptr<Investment, decltype(delInvmt1)> makeInvestment(Ts&&... args);

void delInvmt2(Investment* pInvestment) // �Լ� ������ ������
{
    makeLogEntry(pInvestment);
    delete pInvestment;
};

template<typename... Ts> // ��ȯ Ÿ���� ũ��� Investment*�� ũ�⿡ ��� �Լ� �������� ũ�⸦ ���� ����!
std::unique_ptr<Investment, void (*)(Investment*)> makeInvestment(Ts&&... params);

int main()
{


	return 0;
}