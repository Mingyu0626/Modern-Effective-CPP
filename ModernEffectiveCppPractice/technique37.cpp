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
	vector<int> goodVals; // ���͸� ����� ����

	thread t([&filter, maxVal, &goodVals] // goodVals�� ������ ä���.
		{
			for (auto i = 0; i <= maxVal; i++)
			{
				if (filter(i))
				{
					goodVals.push_back(i);
				}
			}
		});

	auto nh = t.native_handle(); // t�ǳ���Ƽ�� �ڵ��� �̿��Ͽ�, t�� �켱 ������ ����

	if (conditionsAreSatisfied()) // ���ǵ��� �����Ǿ��ٸ�, t�� �ϷḦ ��ٸ���
	{
		t.join();
		performComputation(goodVals); 
		return true; // ����� ����Ǹ�, true ����
	}
	return false; // ����� ������� ������, false ����
}



class ThreadRAII
{
public:
	enum class DtorAction { join, detach };

	ThreadRAII(std::thread&& t, DtorAction a) // �Ҹ��ڿ���, t�� ���� ���� a�� ����
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



// ThreadRAII�� ������ doWork()
bool doWork(std::function<bool(int)> filter, int maxVal = tenMillion)
{
	vector<int> goodVals; // ���͸� ����� ����

	ThreadRAII t(
		std::thread([&filter, maxVal, &goodVals] // goodVals�� ������ ä���.
			{
				for (auto i = 0; i <= maxVal; i++)
				{
					if (filter(i)) goodVals.push_back(i);
				}
			}), 
		ThreadRAII::DtorAction::join
	);

	auto nh = t.get().native_handle(); // t�ǳ���Ƽ�� �ڵ��� �̿��Ͽ�, t�� �켱 ������ ����

	if (conditionsAreSatisfied()) // ���ǵ��� �����Ǿ��ٸ�, t�� �ϷḦ ��ٸ���
	{
		t.get().join();
		performComputation(goodVals);
		return true; // ����� ����Ǹ�, true ����
	}
	return false; // ����� ������� ������, false ����
}


int main()
{


	return 0;
}