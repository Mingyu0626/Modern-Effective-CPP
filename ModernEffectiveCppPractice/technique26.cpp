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
#include <set>

using namespace std;

class Widget {};

multiset<string> names;

template<typename T>
void logAndAdd(T&& name)
{
    auto now = chrono::system_clock::now();
    // log(now, "logAndAdd");
    names.emplace(forward<T>(name));
}

string nameFromIdx(int idx) { return ""; }; // idx�� �ش��ϴ� �̸��� �����ش�

void logAndAdd(int idx) // ���ο� �����ε� �Լ�
{
    auto now = std::chrono::system_clock::now();
    // log(now, "logAndAdd");
    names.emplace(nameFromIdx(idx));
}



class Person
{
public:
    template<typename T> // �Ϻ� ���� ������
    explicit Person(T&& n)
        : name(std::forward<T>(n)) {}

    explicit Person(int idx) // int�� �޴� ������
        : name(nameFromIdx(idx)) {}

private:
    string name;
};



class SpecialPerson : public Person
{
public:
    SpecialPerson(const SpecialPerson& rhs)
        : Person(rhs) {}

    SpecialPerson(SpecialPerson&& rhs)
        : Person(std::move(rhs)) {}
};


int main()
{
    string petName("Darla");
    logAndAdd(petName);
    logAndAdd(string("Persephone"));
    logAndAdd("Patty Dog");
    // ���� T&& ���� ȣ��

    logAndAdd(22); // int ���� ȣ��

    short nameIdx; // nameIdx�� ���� ����
    logAndAdd(nameIdx); // Error! 


    Person p("Nancy");
    auto cloneOfP(p);  // Error!

    const Person p("Nancy");
    auto cloneOfP(p);  // ���� �����ڸ� ȣ��

	return 0;
}