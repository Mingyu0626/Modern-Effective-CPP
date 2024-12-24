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
	return { 1, 2, 3 }; // ����! { 1, 2, 3 }�� ������ ������ �� ����.
}


int main()
{
	auto x = 27; // ��� 3 (x�� �����͵� �ƴϰ�, ������ �ƴϴ�)
	const auto cx = x; // ��� 3 (cx ���� �����͵� �ƴϰ� ������ �ƴϴ�)
	const auto& rx = x; // ��� 1 (rx�� ���� ������ �ƴ� �����̴�)

	auto&& uref1 = x; // x�� int�̸鼭 lvalue�̹Ƿ�, uref1�� ������ int&
	auto&& uref2 = cx; // cx�� const int�̸鼭 lvalue�̹Ƿ�, uref2�� ������ const int&
	auto&& uref3 = 27; // 27�� int�̸鼭 rvalue�̹Ƿ�, uref3�� ������ int&&

	const char name[] = "R. N. Briggs"; // name�� ������ const char[13]
	auto arr1 = name; // arr1�� ������ const char*
	auto& arr2 = name; // arr2�� ������ const char(&)[13]

	void someFunc(int, double); // ������ void(int, double)
	auto func1 = someFunc; // func1�� ������ void(*)(int, double)
	auto& func2 = someFunc; // func2�� ������ void(&)(int, double)

	auto x = { 11, 23, 9 };
	f2({ 11, 23, 9 });

	vector<int> v;
	auto resetV = [&v](const auto& newValue) {v = newValue};
	resetV({ 1, 2, 3 }); // ����! { 1, 2, 3 }�� ������ ������ �� ����.

	return 0;
}