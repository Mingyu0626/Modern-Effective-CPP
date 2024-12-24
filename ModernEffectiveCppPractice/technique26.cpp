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

string nameFromIdx(int idx) { return ""; }; // idx에 해당하는 이름을 돌려준다

void logAndAdd(int idx) // 새로운 오버로딩 함수
{
    auto now = std::chrono::system_clock::now();
    // log(now, "logAndAdd");
    names.emplace(nameFromIdx(idx));
}



class Person
{
public:
    template<typename T> // 완벽 전달 생성자
    explicit Person(T&& n)
        : name(std::forward<T>(n)) {}

    explicit Person(int idx) // int를 받는 생성자
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
    // 전부 T&& 버전 호출

    logAndAdd(22); // int 버전 호출

    short nameIdx; // nameIdx에 값을 배정
    logAndAdd(nameIdx); // Error! 


    Person p("Nancy");
    auto cloneOfP(p);  // Error!

    const Person p("Nancy");
    auto cloneOfP(p);  // 복사 생성자를 호출

	return 0;
}