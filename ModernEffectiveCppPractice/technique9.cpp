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

// FP는 int 1개와 const string& 1개를 받고, 아무것도 돌려주지 않는 함수와 동의어이다.
typedef void (*FP)(int, const string&); // typedef

using FP = void (*) (int, const string&); // 별칭 선언

// 별칭 선언
template<typename T>
using MyAllocList = list<T, MyAlloc<T>>; // MyAllcList<T>는 list<T, MyAlloc<T>>와 동의어이다.

// typedef
template<typename T>
struct MyAllocList
{
	typedef list<T, MyAlloc<T>> type;
};

template<typename T>
class Widget
{
private:
	MyAllocList<T> list;				// 별칭 선언
	typename MyAllocList<T>::type list; // typedef
};

// C++14 미만 버전에서의 형식 특질 변환에 대한 별칭 템플릿을 직접 구현
template <class T>
using remove_const_t = typename remove_const<T>::type;

template <class T>
using remove_reference_t = typename remove_reference<T>::type;

template <class T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;


int main()
{


	return 0;
}