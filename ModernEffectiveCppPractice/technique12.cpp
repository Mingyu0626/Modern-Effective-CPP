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

//class Widget
//{
//public:
//	using DataType = vector<double>;
//
//	DataType& data() { return values; }
//
//private:
//	DataType values;
//};

class Widget
{
public:
	using DataType = vector<double>;

	DataType& data()&
	{
		return values;
	}

	DataType&& data()&&
	{
		return move(values);
	}

private:
	DataType values;
};


int main()
{
	Widget w;
	auto vals1 = w.data(); // w.values를 vals1에 복사

	Widget makeWidget();
	auto vals2 = makeWidget().data(); // DataType&& data()를 호출, vals2는 이동 생성됨
	return 0;
}