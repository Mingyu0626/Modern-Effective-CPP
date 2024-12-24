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
Widget w;
bool f(const Widget& w) {}
const int i = 0;
struct Point{ int x, y; };


// C++11
//template<typename Container, typename Index>
//auto authAndAccess(Container& c, Index i) -> decltype(c[i])
//{
//	authenticateUser();
//	return c[i];
//}

// C++14
//template<typename Container, typename Index>
//auto authAndAccess(Container& c, Index i) 
//{
//	authenticateUser();
//	return c[i];
//}

// C++14
//template<typename Container, typename Index>
//decltype(auto) authAndAccess(Container& c, Index i)
//{
//	authenticateUser();
//	return c[i];
//}

// 최종 C+11 버전
template<typename Container, typename Index>
auto authAndAccess(Container&& c, Index i) 
-> decltype(std::forward<Container>(c)[i])
{
	authenticateUser();
	return std::forward<Container>(c)[i];
}


// 최종 C+14 버전
template<typename Container, typename Index>
decltype(auto) authAndAccess(Container&& c, Index i)
{
	authenticateUser();
	return std::forward<Container>(c)[i];
}

// 리턴문 작성 차이에 따른 함수 반환 형식 연역 결과 차이 in C++14
decltype(auto) f1()
{
	int x = 0;
	return x; // f1은 int를 반환
}

decltype(auto) f2()
{
	int x = 0;
	return (x); // f2는 int&를 반환
}


int main()
{
	if (f(w)) {}
	vector<int> v;
	if (v[0] == 0) {}

	deque<int> dq;
	authAndAccess(dq, 5) = 10;

	Widget w;
	const Widget& cw = w;
	auto myWidget1 = cw; // auto 형식 연역, myWidget1의 형식은 Widget
	decltype(auto) myWidget2 = cw; // decltype 형식 연역, myWidget2의 형식은 const Widget&


	return 0;
}