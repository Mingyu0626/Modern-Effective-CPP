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

void f() // f는 1초간 수면 후 반환
{
	std::this_thread::sleep_for(1s);
}

int main()
{
	auto fut = std::async(f); // 개념적으로는, f를 비동기적으로실행
	while (fut.wait_for(100ms) != std::future_status::ready)
	{
		// f의 실행이 끝날 때까지 루프 반복, 하지만 실행이 끝나지 않을 수도 있다.
	}



	auto fut = std::async(f);
	if (fut.wait_for(0s) == std::future_status::deferred) // 만약 과제가 지연되었다면
	{
		// fut에 wait나 get을 호출해서 f를 동기적으로 호출
	}
	else // 과제가 지연되지 않았다면
	{
		while (fut.wait_for(100ms) != std::future_status::ready)
			// 무한 루프는 불가능(f가 완료된다고 가정할 때)
		{
			// 과제가 지연되지도 않았고, 준비도 되지 않았으므로 준비될 때까지 동시적 작업 수행
		}
		// fut가 준비되었다.
	}



	// std::launch::async를 이용한 과제를 비동기적으로 실행하도록 강제
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