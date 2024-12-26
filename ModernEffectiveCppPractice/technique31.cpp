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

class Widget 
{
public:
	void addFilter() const;

private:
	int divisor;
};

using FilterContainer =
vector<function<bool(int)>>;

FilterContainer filters;

//void addDivisorFilter()
//{
//	auto calc1 = computeSomeValue1();
//	auto calc2 = computeSomeValue2();
//
//	auto divisor = computeDivisor(calc1, calc2);
//
//	filters.emplace_back(
//		[&](int value) { return value % divisor == 0; } // �����ϴ�.
//	);
//}

// �⺻ ���� ĸ�� ��� ���
template<typename C>
void addDivisorFilter(const C& container)
{
	auto calc1 = computeSomeValue1();
	auto calc2 = computeSomeValue2();

	auto divisor = computeDivisor(calc1, calc2);

	using ContElemT = typename C::value_type; // �����̳ʿ� ��� ��ҵ��� ����
	using std::begin;
	using std::end; // �Ϲݼ��� ���� using ���, �׸�13 ����

	if (std::all_of(
		begin(container), end(container),
		[&](const ContElemT& value)
		{ return value % divisor == 0; }) // �����̳��� ��� ���� divisor�� ����ΰ�?
		)
	{
		// �׷� ���
	}
	else
	{
		// �ƴ� ���
	}
}



// �⺻ �� ĸ�� ��� ���
void addDivisorFilter()
{
	auto calc1 = computeSomeValue1();
	auto calc2 = computeSomeValue2();

	auto divisor = computeDivisor(calc1, calc2);

	filters.emplace_back(
		[=](int value) { return value % divisor == 0; } // ������ divisor�� ����� ���� �ʴ´�.
	);
}



// �⺻ ĸ�� ��带 ���ϴ� [=]�� = ����
void Widget::addFilter() const
{
	filters.emplace_back(
		[](int value) { return value % divisor == 0; } // Error!
	);
}

// divisor�� ������� ������ ĸ��
void Widget::addFilter() const
{
	filters.emplace_back(
		[divisor](int value)                           // Error!
		{ return value % divisor == 0; }
	);
}

// divisor�� ���� ������ �����Ͽ� �ذ�
// C++11
void Widget::addFilter() const
{
	auto divisorCopy = divisor; // �ڷ� ����� ����
	filters.emplace_back(
		[divisorCopy](int value) // ���纻�� ĸ��
		{ return value % divisorCopy == 0; } // OK!
	);
}

// �⺻ ĸ�� ��� ���, But ���� ������ ������ �ʿ�� ����. �׳� ����ó�� ���������.
void Widget::addFilter() const
{
	auto divisorCopy = divisor; // �ڷ� ����� ����
	filters.emplace_back(
		[=](int value) // ���纻�� ĸ��
		{ return value % divisorCopy == 0; } // OK!
	);
}

// C++14
void Widget::addFilter() const
{
	filters.emplace_back(
		[divisor = divisor](int value) // divisor�� Ŭ������ ����
		{ return value % divisor == 0; } // OK!
	);
}



// static ������ ����� ����
void addDivisorFilter()
{
	static auto calc1 = computeSomeValue1();
	static auto calc2 = computeSomeValue2();

	static auto divisor =
		computeDivisor(calc1, calc2);

	filters.emplace_back(
		[=](int value) // �ƹ� �͵� ĸ������ �ʴ´�.
		{ return value % divisor == 0; } // �� ���� ���� divisor�� ��Ī�Ѵ�.
	);

	++divisor; // divisor�� �����Ѵ�.
}

int main()
{


	return 0;
}