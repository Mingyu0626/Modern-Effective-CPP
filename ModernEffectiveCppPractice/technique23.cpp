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
#include <type_traits>

using namespace std;

class Widget;

// C++11
template<typename T>
typename remove_reference<T>::type&& move(T&& param)
{
	using ReturnType = typename remove_reference<T>::type&&; // ��Ī ����, �׸�9 ����
	return static_cast<ReturnType>(param);
}

// C++14
template<typename T>
decltype(auto) move(T&& param)
{
	using ReturnType = remove_reference_t<T>&&; // ��Ī ����, �׸�9 ����
	return static_cast<ReturnType>(param);
}



class Annotation
{
public:
	explicit Annotation(const string text)
		: value(std::move(text)) {} // string�� �̵� ������ ��û������, ��û ����� const�� ���� ������ �߻�
private:
	const string value;
};



void process(const Widget& lvalArg) { cout << "lvalue process\n"; }
void process(Widget&& rvalArg) { cout << "rvalue process\n"; }

template <typename T> // param�� process�� �Ѱ��ִ� ���ø�
void logAndProcess(T&& param)
{
	auto now = std::chrono::system_clock::now();
	// makeLogEntry("Calling 'process'", now);
	process(std::forward<T>(param));
}


class Widget
{
public:
	Widget() {}

	// std::move()�� �̿��� ����
	Widget(Widget&& rhs)
		: s(std::move(rhs.s))
	{
		++moveCtorCalls;
	}

	// std::forward()�� �̿��� ����
	Widget(Widget&& rhs)
		: s(std::forward<string>(rhs.s))
	{
		++moveCtorCalls;
	}

private:
	size_t moveCtorCalls;
	string s;
};




int main()
{
	Widget w;
	logAndProcess(w); // lvalue�� ȣ��
	logAndProcess(std::move(w)); // rvalue�� ȣ��

	return 0;
}