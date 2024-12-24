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
void f2(const T& param) // param이 const에 대한 참조
{}

template<typename T>
void f3(T* param) // param이 포인터
{}

template<typename T>
void f4(T&& param) // param이 보편 참조
{}

template<typename T>
void f5(T param) {} // param이 값으로 전달

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
	int x = 27; // x는 int
	const int cx = x; // cs는 const int
	const int& rx = x; // rx는 const int인 x에 대한 참조

	f(x); // T는 int, param의 형식은 int&
	f(cx); // T는 const int, param의 형식은 const int&
	f(rx); // T는 const int, param의 형식은 const int&

	f2(x); // T는 int, param의 형식은 const int&
	f2(cx); // T는 int, param의 형식은 const int&
	f2(rx); // T는 int, param의 형식은 const int&


	const int* px = &x;
	f3(&x); // T는 int, param의 형식은 int*
	f3(px); // T는 const int, param의 형식은 const int*


	f4(x); // x는 lvalue이므로, T는 int&, param은 int&
	f4(cx); // x는 lvalue이므로, T는 const int&, param은 const int&
	f4(rx); // x는 lvalue이므로, T는 const int&, param은 const int&
	f4(27); // x는 rvalue이므로, T는 int, param은 int&&

	f5(x); // T는 int, param의 형식은 int
	f5(cx); // T는 const int, param의 형식은 int
	f5(rx); // T는 const int, param의 형식은 int


	const char* const ptr = "Fun with pointers"; // const 객체를 가리키는 const 포인터
	f5(ptr); // const char* const 형식의 인수를 전달


	const char name[] = "J. P. Briggs"; // name의 형식은 const char[13]
	const char* ptrToName = name; // 배열이 포인터로 붕괴된다.

	f6(name);
	f7(name);

	int keyVals[] = { 1, 3, 7, 9, 11, 22, 35 };
	int mappedVals[arraySize(keyVals)];
	// array<int, arraySize(keyVals)> mappedVals;

	f8(someFunc); // T는 void(*)(int, double), param은 함수 포인터로 연역
	f9(someFunc); // T는 void(&)(int, double), param은 함수 참조로 연역

	return 0;
}