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
#include <unordered_map>

using namespace std;

class Widget {};

//template<typename It>
//void dwim(It b, It e) // b ~ e ������ �ִ� ��� ��ҿ� ����, dwim(do what I mean)�� ����
//{
//	for (; b != e; ++b)
//	{
//		typename std::iterator_traits<It>::value_type
//			currValue = *b;
//	}
//}

template<typename It>
void dwim(It b, It e) // b ~ e ������ �ִ� ��� ��ҿ� ����, dwim(do what I mean)�� ����
{
	for (; b != e; ++b)
	{
		auto currValue = *b;
	}
}

auto derefUPLess =
[](const std::unique_ptr<Widget>& p1,
	const std::unique_ptr<Widget>& p2)
	{ return *p1 < *p2; };

auto derefUPLess =
[](const auto& p1,
	const auto& p2)
	{ return *p1 < *p2; };

int main()
{
	std::vector<int> v;
	unsigned sz = v.size();  // �ü���� ���� ���� �߻� ����
	auto sz = v.size();  	 // �ذ�

	std::unordered_map<std::string, int> m;
	for (const std::pair<std::string, int>& p : m)
	{
		
	}

	return 0;
}