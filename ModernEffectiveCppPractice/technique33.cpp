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

auto f = [](auto x) { return normalize(x); };

class 컴파일러가_생성한_클래스
{
public:
	template<typename T>
	auto operator()(T x) const
	{
		return normalize(x);
	}
};



int main()
{
	auto f = [](auto&& x)
		{ return normalize(std::forward<decltype(x)>(x)); };

	auto f2 = [](auto&&... xs)
		{ return normalize(std::forward<decltype(xs)>(xs)...); };

	return 0;
}