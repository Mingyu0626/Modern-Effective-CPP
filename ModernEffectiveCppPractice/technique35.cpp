#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
#include <thread>
#include <future>
#include <mutex>
#include <cassert>
#include <functional>
#include <new>
#include <utility>

using namespace std;

class Widget {};

int doAsyncWork() {}
thread t(doAsyncWork); // 스레드 기반

auto fut = async(doAsyncWork); // 과제 기반, fut는 future를 의미한다.
// 스레드 관리 부담을 STL 구현자들에게 떠넘긴다.

int doAsyncWork() noexcept;
std::thread t(doAsyncWork);
// 사용 가능한 스레드가 없으면, doAsyncWork가 noexcept여도 예외 발생

int main()
{


	return 0;
}