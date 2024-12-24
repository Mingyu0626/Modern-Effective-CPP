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

string nameFromIdx(int idx) { return ""; }; // idx�� �ش��ϴ� �̸��� �����ش�
class Person // �� ���� ����� �Ű����� ��� ���
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
template<typename T> // ����ǥ ��� ��� ���
void logAndAdd(T&& name)
{
	logAndAddImpl(std::forward<T>(name),
		is_integral<remove_reference_t<T>>());
}

template<typename T> // ���� Ÿ���� �ƴ� ���
void logAndAddImpl(T&& name, std::false_type)
{
	auto now = std::chrono::system_clock::now();
	log(now, "logAndAdd");
	names.emplace(std::forward<T>(name));
}
void logAndAddImpl(int idx, std::true_type) // ���� Ÿ���� ���
{
	logAndAdd(nameFromIdx(idx));
}



// C++11���� �Ļ� Ŭ���������� �Ϻ� ���� ������ ȣ�� ���� ����
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
// C++14���� �Ļ� Ŭ���������� �Ϻ� ���� ������ ȣ�� ���� ����
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



// ���� Ÿ�� �������� �ذ��� �Ϻ��� ���� in C++14
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



// static_assert�� �̿��� char16_t ���� ���� �޽��� ���
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
    explicit Person(T&& n) // string�̳�, string���� ��ȯ�Ǵ� �μ����� ���� ������
        : name(std::forward<T>(n))
    {
        static_assert(
            std::is_constructible<stringm T>::value,
            "Parameter n can't be used to construct a string"
            );
    }
    explicit Person(int idx) // ���� �μ����� ó���ϴ� Person ������
        : name(nameFromIdx(idx)) {}
private:
    std::string name;
};



int main()
{


	return 0;
}