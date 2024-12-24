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

// FP�� int 1���� const string& 1���� �ް�, �ƹ��͵� �������� �ʴ� �Լ��� ���Ǿ��̴�.
typedef void (*FP)(int, const string&); // typedef

using FP = void (*) (int, const string&); // ��Ī ����

// ��Ī ����
template<typename T>
using MyAllocList = list<T, MyAlloc<T>>; // MyAllcList<T>�� list<T, MyAlloc<T>>�� ���Ǿ��̴�.

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
	MyAllocList<T> list;				// ��Ī ����
	typename MyAllocList<T>::type list; // typedef
};

// C++14 �̸� ���������� ���� Ư�� ��ȯ�� ���� ��Ī ���ø��� ���� ����
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