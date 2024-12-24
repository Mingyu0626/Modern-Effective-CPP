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
#include <array>

using namespace std;

class Widget {};

int sz; // 비constexpr 변수
// constexpr auto arraySize1 = sz; // Error! sz값이 컴파일 도중 알려지지 않음
// array<int, sz> data1; // Error! 위와 동일한 문제

constexpr auto arraySize2 = 10; // 10은 확실히 컴파일 시점에 정의
array<int, arraySize2> data2; // arraySize2는 constexpr 객체이므로 문제X

// const auto arraySize = sz;
// array<int, arraySize> data; // Error! arraySize 값은 컴파일 시점에서 알려지지 않음



// C++11
//constexpr int pow(int base, int exp) noexcept
//{
//	return (exp == 0 ? 1 : base * pow(base, exp - 1));
//}

// C++14
constexpr int pow(int base, int exp) noexcept
{
	auto result = 1;
	for (int i = 0; i < exp; i++) result *= base;
	return result;
}

constexpr auto numConds = 5; // 조건들의 개수
array<int, pow(3, numConds)> results; // results 개의 3^numConds 개의 요소들을 담는다.


class Point
{
public:
	constexpr Point(double xVal = 0, double yVal = 0) noexcept
		: x(xVal), y(yVal) 
	{}

	constexpr double xValue() const noexcept { return x; }
	constexpr double yValue() const noexcept { return y; }

	// C++11
	// void setX(double newX) noexcept { x = newX; }
	// void setY(double newY) noexcept { y = newY; }
	
	// C++14
	constexpr void setX(double newX) noexcept { x = newX; }
	constexpr void setY(double newY) noexcept { y = newY; }

private:
	double x, y;
};

constexpr
Point midpoint(const Point& p1, const Point& p2) noexcept
{
	return { (p1.xValue() + p2.xValue()) / 2, (p1.yValue() + p2.yValue()) / 2 };
	// constexpr 멤버 함수들을 호출
}


int main()
{
	constexpr Point p1(9.4, 27.7);
	constexpr Point p2(28.8, 5.3);

	constexpr auto mid = midpoint(p1, p2);
	return 0;
}