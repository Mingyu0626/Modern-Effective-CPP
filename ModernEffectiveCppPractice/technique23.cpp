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
	using ReturnType = typename remove_reference<T>::type&&; // 별칭 선언, 항목9 참고
	return static_cast<ReturnType>(param);
}

// C++14
template<typename T>
decltype(auto) move(T&& param)
{
	using ReturnType = remove_reference_t<T>&&; // 별칭 선언, 항목9 참고
	return static_cast<ReturnType>(param);
}



class Annotation
{
public:
	explicit Annotation(const string text)
		: value(std::move(text)) {} // string의 이동 연산을 요청했지만, 요청 대상이 const라 복사 연산이 발생
private:
	const string value;
};



void process(const Widget& lvalArg) { cout << "lvalue process\n"; }
void process(Widget&& rvalArg) { cout << "rvalue process\n"; }

template <typename T> // param을 process에 넘겨주는 템플릿
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

	// std::move()를 이용한 구현
	Widget(Widget&& rhs)
		: s(std::move(rhs.s))
	{
		++moveCtorCalls;
	}

	// std::forward()를 이용한 구현
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
	logAndProcess(w); // lvalue로 호출
	logAndProcess(std::move(w)); // rvalue로 호출

	return 0;
}