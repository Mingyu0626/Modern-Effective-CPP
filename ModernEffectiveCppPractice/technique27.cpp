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

string nameFromIdx(int idx) { return ""; }; // idx에 해당하는 이름을 돌려준다
class Person // 값 전달 방식의 매개변수 사용 기법
{
public:
	explicit Person(string n)
		: name(std::move(n)) {}

	explicit Person(int idx)
		: name(nameFromIdx(idx)) {}

private:
	string name;
};

std::multiset<std::string> names;
template<typename T> // 꼬리표 배분 사용 기법
void logAndAdd(T&& name)
{
	logAndAddImpl(std::forward<T>(name),
		is_integral<remove_reference_t<T>>());
}

template<typename T> // 정수 타입이 아닌 경우
void logAndAddImpl(T&& name, std::false_type)
{
	auto now = std::chrono::system_clock::now();
	log(now, "logAndAdd");
	names.emplace(std::forward<T>(name));
}
void logAndAddImpl(int idx, std::true_type) // 정수 타입인 경우
{
	logAndAdd(nameFromIdx(idx));
}



// C++11에서 파생 클래스에서의 완벽 전달 생성자 호출 방지 설계
class Person {
public:
    template<
        typename T,
        typename = typename std::enable_if<
        !std::is_base_of<Person,
        typename std::decay<T>::type
        >::value
        >::type
    >
    explicit Person(T&& n);
};
// C++14에서 파생 클래스에서의 완벽 전달 생성자 호출 방지 설계
class Person {
public:
    template<
        typename T,
        typename = std::enable_if_t<
        !std::is_base_of<Person,
        std::decay_t<T>
        >::value
        >
    >
    explicit Person(T&& n);
};



// 정수 타입 문제까지 해결한 완벽한 버전 in C++14
class Person
{
public:
    template<
        typename T,
        typename = std::enable_if_t<
        !std::is_base_of<Person, std::decay_t<T>>::value
        &&
        !std::is_integral<std::remove_reference_t<T>>::value
        >
    >
    explicit Person(T&& n)
        : name(std::forward<T>(n)) {}
    explicit Person(int idx)
        : name(nameFromIdx(idx)) {}
private:
    std::string name;
};



// static_assert를 이용한 char16_t 사용시 오류 메시지 출력
class Person
{
public:
    template<
        typename T,
        typename = std::enable_if_t<
        !std::is_base_of<Person, std::decay_t<T>>::value
        &&
        !std::is_integral<std::remove_reference_t<T>>::value
        >
    >
    explicit Person(T&& n) // string이나, string으로 변환되는 인수들을 위한 생성자
        : name(std::forward<T>(n))
    {
        static_assert(
            std::is_constructible<stringm T>::value,
            "Parameter n can't be used to construct a string"
            );
    }
    explicit Person(int idx) // 정수 인수들을 처리하는 Person 생성자
        : name(nameFromIdx(idx)) {}
private:
    std::string name;
};



int main()
{


	return 0;
}