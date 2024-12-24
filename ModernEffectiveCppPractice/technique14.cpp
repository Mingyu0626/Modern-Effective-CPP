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

int func() throw();  // C++98 스타일, func 함수는 예외를 방출하지 않음
int func() noexcept; // C++11 스타일, func 함수는 예외를 방출하지 않음

template <class T, size_t N>
void swap(T(&a)[N], T(&b)[N]) noexcept(noexcept(swap(*a, *b)));

template <class T1, class T2>
struct pair
{
	void swap(pair& p) noexcept(noexcept(noexcept(swap(first, p.first)) &&
		noexcept(swap(second, p.second)));
};

int main()
{


	return 0;
}