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

class Widget {};

void f(int); // f�� 3���� �����ε� ����
void f(bool);
void f(void*);


// �� �Լ����� ������ ���ؽ��� ��װ� ȣ���ؾ� �Ѵ�.
int f1(shared_ptr<Widget> spw) { return 0; }
double f2(unique_ptr<Widget> upw) { return 0.0; }
bool f3(Widget* pw) { return true; }

template<typename FuncType, typename MuxType, typename PtrType>
decltype(auto) lockAndCall(FuncType func, MuxType& mutex, PtrType ptr)
{
	using MuxGuard = lock_guard<MuxType>;

	MuxGuard g(mutex);
	return func(ptr);
}



int main()
{
	//f(0); // f(int)�� ȣ��
	//f(NULL); // ������ f(int)�� ȣ��, �����ϵ��� ���� ���� ����
	//f(nullptr); // f(void*)�� ȣ��



	mutex f1m, f2m, f3m;
	using MuxGuard = lock_guard<mutex>;

	{
		MuxGuard g(f1m);
		auto result = f1(0);
	}

	{
		MuxGuard g(f2m);
		auto result = f2(NULL);
	}

	{
		MuxGuard g(f3m);
		auto result = f3(nullptr);
	}


	auto reuslt1 = lockAndCall(f1, f1m, 0); // Error!
	auto reuslt2 = lockAndCall(f2, f2m, NULL); // Error!
	auto reuslt3 = lockAndCall(f3, f3m, nullptr); // ���� �۵�



	return 0;
}