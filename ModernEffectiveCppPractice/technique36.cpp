#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
#include <thread>
#include <mutex>
#include <future>
#include <cassert>
#include <functional>
#include <new>
#include <utility>

using namespace std;
using namespace std::literals;

class Widget {};

void f() // f�� 1�ʰ� ���� �� ��ȯ
{
	std::this_thread::sleep_for(1s);
}

int main()
{
	auto fut = std::async(f); // ���������δ�, f�� �񵿱������ν���
	while (fut.wait_for(100ms) != std::future_status::ready)
	{
		// f�� ������ ���� ������ ���� �ݺ�, ������ ������ ������ ���� ���� �ִ�.
	}



	auto fut = std::async(f);
	if (fut.wait_for(0s) == std::future_status::deferred) // ���� ������ �����Ǿ��ٸ�
	{
		// fut�� wait�� get�� ȣ���ؼ� f�� ���������� ȣ��
	}
	else // ������ �������� �ʾҴٸ�
	{
		while (fut.wait_for(100ms) != std::future_status::ready)
			// ���� ������ �Ұ���(f�� �Ϸ�ȴٰ� ������ ��)
		{
			// ������ ���������� �ʾҰ�, �غ� ���� �ʾ����Ƿ� �غ�� ������ ������ �۾� ����
		}
		// fut�� �غ�Ǿ���.
	}



	// std::launch::async�� �̿��� ������ �񵿱������� �����ϵ��� ����
	auto fut = std::async(std::launch::async, f);

	return 0;
}

// C++11
template<typename F, typename... Ts>
inline std::future<typename std::result_of<F(Ts...)>::type>
reallyAsync(F&& f, Ts&&... params)
{
	return std::async(std::launch::async,
		std::forward<F>(f),
		std::forward<Ts>(params)...);
}

// C++14
template<typename F, typename... Ts>
inline auto reallyAsync(F&& f, Ts&&... params)
{
	return std::async(std::launch::async,
		std::forward<F>(f),
		std::forward<Ts>(params)...);
}