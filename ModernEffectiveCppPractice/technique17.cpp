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
#include <map>

using namespace std;

//class Widget 
//{
//public:
//	Widget(Widget&& rhs); // 이동 생성자
//	Widget& operator=(Widget&& rhs); // 이동 배정 연산자
//};



class Widget
{
public:
	~Widget();
	Widget(const Widget&) = default; // 기본 복사 생성자
	Widget& operator=(const Widget&) = default; // 기본 복사 대입 연산자
};



class Base
{
public:
	virtual ~Base() = default; // 소멸자를 가상으로
	Base(Base&&) = default; // 기본 이동 생성자
	Base& operator=(Base&&) = default; // 기본 이동 대입 연산자

	Base(const Base&) = default; // 기본 복사 생성자
	Base& operator=(const Base&) = default; // 기본 복사 대입 연산자
};



class StringTable
{
public:
	StringTable()
	{
		makeLogEntry("Creating StringTable object");
	}

	~StringTable()
	{
		makeLogEntry("Destroying StringTable object");
	}
private:
	map<int, string> values;
};

class Widget
{
	template<typename T>
	Widget(const T& rhs); // 그 어떤 것으로도 Widget을 생성

	template<typename T>
	Widget& operator=(const T& rhs); // 그 어떤 것으로도 Widget을 복사 대입(배정)
};




int main()
{


	return 0;
}