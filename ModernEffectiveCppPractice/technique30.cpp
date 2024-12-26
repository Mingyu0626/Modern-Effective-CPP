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

void f(const vector<int>& v);
void f(size_t val);
void f(int (*pf)(int));
void f(int pf(int));
void f(std::size_t sz);

template<typename T>
void fwd(T&& param)
{
	f(std::forward<T>(param));
}
template<typename... Ts>
void fwd(Ts&&... params)
{
	f(std::forward<Ts>(params)...);
}



void f(const vector<int>& v) {}
void f(size_t val) {}



class Widget
{
public:

	static constexpr size_t MinVals = 28; // MinVals의 선언
};
constexpr std::size_t Widget::MinVals; // MinVals의 정의



void f(int (*pf)(int)) {}
void f(int pf(int)) {}

int processVal(int value);
int processVal(int value, int priority);

template<typename T>
T workOnVal(T param)
{
	...
}

// 전달하고자 하는 오버로딩 or 템플릿 인스턴스를 명시적으로 지정
using ProcessFuncType = int (*)(int);



struct IPv4Header {
	std::uint32_t version : 4,
		IHL : 4,
		DSCP : 6,
		ECN : 2,
		totalLength : 16;
};

void f(std::size_t sz) {}


int main()
{
	// f({ 1, 2, 3 }); // {1, 2, 3}은 암묵적으로 vector<int>로 변환
	// fwd({ 1, 2, 3 }); // Error!



	//vector<int> widgetData;
	//widgetData.reserve(Widget::MinVals); // MinVals를 사용



	f(Widget::MinVals);     // OK
	fwd(Widget::MinVals);   // 링크 성공 in VS 2022, But 다른 컴파일러에서는 실패할 가능성 농후



	f(processVal); // OK!

	fwd(processVal); // Error!
	fwd(workOnVal);    // Error!

	ProcessFuncType processValPtr = processVal;
	fwd(processValPtr);
	fwd(static_cast<ProcessFuncType>(workOnVal));



	IPv4Header h;
	f(h.totalLength);   // OK
	fwd(h.totalLength); // Error!

	auto length = static_cast<std::uint16_t>(h.totalLength);
	fwd(length); // OK

	return 0;
}