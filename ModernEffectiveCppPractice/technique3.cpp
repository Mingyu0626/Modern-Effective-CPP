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

// ���� C+11 ����
template<typename Container, typename Index>
auto authAndAccess(Container&& c, Index i) 
-> decltype(std::forward<Container>(c)[i])
{
	authenticateUser();
	return std::forward<Container>(c)[i];
}


// ���� C+14 ����
template<typename Container, typename Index>
decltype(auto) authAndAccess(Container&& c, Index i)
{
	authenticateUser();
	return std::forward<Container>(c)[i];
}

// ���Ϲ� �ۼ� ���̿� ���� �Լ� ��ȯ ���� ���� ��� ���� in C++14
decltype(auto) f1()
{
	int x = 0;
	return x; // f1�� int�� ��ȯ
}

decltype(auto) f2()
{
	int x = 0;
	return (x); // f2�� int&�� ��ȯ
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
	auto myWidget1 = cw; // auto ���� ����, myWidget1�� ������ Widget
	decltype(auto) myWidget2 = cw; // decltype ���� ����, myWidget2�� ������ const Widget&


	return 0;
}