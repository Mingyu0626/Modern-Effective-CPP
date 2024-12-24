#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <cassert>
#include <functional>
#include <new>

using namespace std;

template<typename T>
void f1(T param) {}

template<typename T>
void f2(initializer_list<T> initList) {}

auto createInitList()
{
	return { 1, 2, 3 }; // 에러! { 1, 2, 3 }의 형식을 연역할 수 없다.
}


int main()
{
	auto x = 27; // 경우 3 (x는 포인터도 아니고, 참조도 아니다)
	const auto cx = x; // 경우 3 (cx 역시 포인터도 아니고 참조도 아니다)
	const auto& rx = x; // 경우 1 (rx는 보편 참조가 아닌 참조이다)

	auto&& uref1 = x; // x는 int이면서 lvalue이므로, uref1의 형식은 int&
	auto&& uref2 = cx; // cx는 const int이면서 lvalue이므로, uref2의 형식은 const int&
	auto&& uref3 = 27; // 27은 int이면서 rvalue이므로, uref3의 형식은 int&&

	const char name[] = "R. N. Briggs"; // name의 형식은 const char[13]
	auto arr1 = name; // arr1의 형식은 const char*
	auto& arr2 = name; // arr2의 형식은 const char(&)[13]

	void someFunc(int, double); // 형식은 void(int, double)
	auto func1 = someFunc; // func1의 형식은 void(*)(int, double)
	auto& func2 = someFunc; // func2의 형식은 void(&)(int, double)

	auto x = { 11, 23, 9 };
	f2({ 11, 23, 9 });

	vector<int> v;
	auto resetV = [&v](const auto& newValue) {v = newValue};
	resetV({ 1, 2, 3 }); // 에러! { 1, 2, 3 }의 형식을 연역할 수 없다.

	return 0;
}