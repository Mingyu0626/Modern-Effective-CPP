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
thread t(doAsyncWork); // ������ ���

auto fut = async(doAsyncWork); // ���� ���, fut�� future�� �ǹ��Ѵ�.
// ������ ���� �δ��� STL �����ڵ鿡�� ���ѱ��.

int doAsyncWork() noexcept;
std::thread t(doAsyncWork);
// ��� ������ �����尡 ������, doAsyncWork�� noexcept���� ���� �߻�

int main()
{


	return 0;
}