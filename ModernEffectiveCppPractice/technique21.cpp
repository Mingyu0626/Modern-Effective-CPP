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
#include <unordered_map>

using namespace std;

class Widget {};

auto upw1(std::make_unique<Widget>()); // make 함수를 사용
std::unique_ptr<Widget> upw2(new Widget); // 사용하지 않음
auto spw1(std::make_shared<Widget>()); // make 함수를 사용
std::shared_ptr<Widget> spw2(new Widget); // 사용하지 않음



void processWidget(std::shared_ptr<Widget> spw, int priority) {}
int computePriority(void) {}



auto widgetDeleter = [](Widget* pw) {};
unique_ptr<Widget, decltype(widgetDeleter)>
upw(new Widget, widgetDeleter);

shared_ptr<Widget> spw(new Widget, widgetDeleter);



// std::initializer_list 객체를 생성
auto initList = { 10, 20 };
// 그 std::initializer_list 객체를 이용해서 std::vector를 생성
auto spv = std::make_shared<std::vector<int>>(initList);



class ReallyBigType {};

// 아주 큰 객체를 std::make_shared를 이용해서 생성
auto pBigObj = std::make_shared<ReallyBigType>();



int main()
{
	// 자원 누수 위험이 있음!
	processWidget(std::shared_ptr<Widget>(new Widget), computePriority());
	// 자원 누수의 위험이 없음
	processWidget(std::make_shared<Widget>(), computePriority());
	return 0;
}