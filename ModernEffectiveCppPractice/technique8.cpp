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

void f(int); // f의 3가지 오버로드 버전
void f(bool);
void f(void*);


// 이 함수들은 적절한 뮤텍스를 잠그고 호출해야 한다.
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
	//f(0); // f(int)를 호출
	//f(NULL); // 보통은 f(int)를 호출, 컴파일되지 않을 수도 있음
	//f(nullptr); // f(void*)를 호출



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
	auto reuslt3 = lockAndCall(f3, f3m, nullptr); // 정상 작동



	return 0;
}