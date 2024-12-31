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

constexpr auto tenMillion = 10'000'000;

bool doWork(std::function<bool(int)> filter, int maxVal = tenMillion)
{
	vector<int> goodVals; // 필터를 통과한 값들

	thread t([&filter, maxVal, &goodVals] // goodVals에 값들을 채운다.
		{
			for (auto i = 0; i <= maxVal; i++)
			{
				if (filter(i))
				{
					goodVals.push_back(i);
				}
			}
		});

	auto nh = t.native_handle(); // t의네이티브 핸들을 이용하여, t의 우선 순위를 설정

	if (conditionsAreSatisfied()) // 조건들이 만족되었다면, t의 완료를 기다린다
	{
		t.join();
		performComputation(goodVals); 
		return true; // 계산이 수행되면, true 리턴
	}
	return false; // 계산이 수행되지 않으면, false 리턴
}



class ThreadRAII
{
public:
	enum class DtorAction { join, detach };

	ThreadRAII(std::thread&& t, DtorAction a) // 소멸자에서, t에 대해 동작 a를 수행
		: action(a), t(std::move(t)) {}

	~ThreadRAII() 
	{
		if (t.joinable())
		{
			if (action == DtorAction::join)
			{
				t.join();
			}
			else
			{
				t.detach();
			}
		}
	}

	ThreadRAII(ThreadRAII&&) = default;
	ThreadRAII& operator=(ThreadRAII&&) = default;

	std::thread& get() { return t; }

private:
	DtorAction action;
	std::thread t;
};



// ThreadRAII를 적용한 doWork()
bool doWork(std::function<bool(int)> filter, int maxVal = tenMillion)
{
	vector<int> goodVals; // 필터를 통과한 값들

	ThreadRAII t(
		std::thread([&filter, maxVal, &goodVals] // goodVals에 값들을 채운다.
			{
				for (auto i = 0; i <= maxVal; i++)
				{
					if (filter(i)) goodVals.push_back(i);
				}
			}), 
		ThreadRAII::DtorAction::join
	);

	auto nh = t.get().native_handle(); // t의네이티브 핸들을 이용하여, t의 우선 순위를 설정

	if (conditionsAreSatisfied()) // 조건들이 만족되었다면, t의 완료를 기다린다
	{
		t.get().join();
		performComputation(goodVals);
		return true; // 계산이 수행되면, true 리턴
	}
	return false; // 계산이 수행되지 않으면, false 리턴
}


int main()
{


	return 0;
}