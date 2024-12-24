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

template<typename T>
void func(T&& param);

template<typename T>
T&& forward(remove_reference_t<T>& param)
{
	return static_cast<T&&>(param);
}

class Widget {};

template<typename T>
class WidgetTemplate 
{
public:
	typedef T&& RvalueRefToT;
	
};


int main()
{
	Widget widgetFactory();   // rvalue를 돌려주는 함수
	Widget w;
	func(w);
	func(widgetFactory());

	auto&& w1 = w; // w1은 lvalue 참조
	auto&& w2 = widgetFactory(); // w2는 rvalue 참조



	WidgetTemplate<int&> w;   // int&로 선언
	typedef int& RvalueRefToT; // lvalue에 대한 typedef가 됨.

	return 0;
}