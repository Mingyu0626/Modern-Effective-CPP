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
	Widget widgetFactory();   // rvalue�� �����ִ� �Լ�
	Widget w;
	func(w);
	func(widgetFactory());

	auto&& w1 = w; // w1�� lvalue ����
	auto&& w2 = widgetFactory(); // w2�� rvalue ����



	WidgetTemplate<int&> w;   // int&�� ����
	typedef int& RvalueRefToT; // lvalue�� ���� typedef�� ��.

	return 0;
}