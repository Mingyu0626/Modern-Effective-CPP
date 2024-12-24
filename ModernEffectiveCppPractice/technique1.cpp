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
void f(T& param)
{}

template<typename T>
void f2(const T& param) // param�� const�� ���� ����
{}

template<typename T>
void f3(T* param) // param�� ������
{}

template<typename T>
void f4(T&& param) // param�� ���� ����
{}

template<typename T>
void f5(T param) {} // param�� ������ ����

template<typename T>
void f6(T param) {}

template<typename T>
void f7(T& param) {}


template<typename T, size_t N>
constexpr size_t arraySize(T(&)[N]) noexcept
{
	return N;
}

void someFunc(int, double);

template<typename T>
void f8(T param) {}

template<typename T>
void f9(T& param) {}

int main()
{
	int x = 27; // x�� int
	const int cx = x; // cs�� const int
	const int& rx = x; // rx�� const int�� x�� ���� ����

	f(x); // T�� int, param�� ������ int&
	f(cx); // T�� const int, param�� ������ const int&
	f(rx); // T�� const int, param�� ������ const int&

	f2(x); // T�� int, param�� ������ const int&
	f2(cx); // T�� int, param�� ������ const int&
	f2(rx); // T�� int, param�� ������ const int&


	const int* px = &x;
	f3(&x); // T�� int, param�� ������ int*
	f3(px); // T�� const int, param�� ������ const int*


	f4(x); // x�� lvalue�̹Ƿ�, T�� int&, param�� int&
	f4(cx); // x�� lvalue�̹Ƿ�, T�� const int&, param�� const int&
	f4(rx); // x�� lvalue�̹Ƿ�, T�� const int&, param�� const int&
	f4(27); // x�� rvalue�̹Ƿ�, T�� int, param�� int&&

	f5(x); // T�� int, param�� ������ int
	f5(cx); // T�� const int, param�� ������ int
	f5(rx); // T�� const int, param�� ������ int


	const char* const ptr = "Fun with pointers"; // const ��ü�� ����Ű�� const ������
	f5(ptr); // const char* const ������ �μ��� ����


	const char name[] = "J. P. Briggs"; // name�� ������ const char[13]
	const char* ptrToName = name; // �迭�� �����ͷ� �ر��ȴ�.

	f6(name);
	f7(name);

	int keyVals[] = { 1, 3, 7, 9, 11, 22, 35 };
	int mappedVals[arraySize(keyVals)];
	// array<int, arraySize(keyVals)> mappedVals;

	f8(someFunc); // T�� void(*)(int, double), param�� �Լ� �����ͷ� ����
	f9(someFunc); // T�� void(&)(int, double), param�� �Լ� ������ ����

	return 0;
}