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

//template<class charT, class traits = char_traits<charT>>
//class basic_ios : public ios_base 
//{
//public:
//	
//private:
//	basic_ios(const basic_ios&); // not defined
//	basic_ios& operator=(const basic_ios&); // not defined
//};

template<class charT, class traits = char_traits<charT>>
class basic_ios : public ios_base
{
public:
	basic_ios(const basic_ios&) = delete;
	basic_ios& operator=(const basic_ios&) = delete;
};

bool isLucky(int number) { return number == 7; }
bool isLucky(char) = delete; // char 배제
bool isLucky(bool) = delete; // bool 배제
bool isLucky(double) = delete; // double과 float 배제

template<typename T>
void processPointer(T* ptr);

template<>
void processPointer<void>(void* ptr) = delete;
template<>
void processPointer<const void>(const void* ptr) = delete;
template<>
void processPointer<char>(char* ptr) = delete;
template<>
void processPointer<const char>(const char* ptr) = delete;


class Widget 
{
public:
	template<typename T>
	void processPointer(T* ptr) {}

private:
	template<>
	void processPointer<void>(void*);
};


class Widget
{
public:
	template<typename T>
	void processPointer(T* ptr) {}
};
template<>
void processPointer<void>(void*) = delete; // 여전히 public이지만, 삭제되었다.


int main()
{
	/*if (isLucky('a')) {}
	if (isLucky(true)) {}
	if (isLucky(3.5)) {}*/

	return 0;
}