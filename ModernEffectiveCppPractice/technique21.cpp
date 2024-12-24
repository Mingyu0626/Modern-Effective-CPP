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

auto upw1(std::make_unique<Widget>()); // make �Լ��� ���
std::unique_ptr<Widget> upw2(new Widget); // ������� ����
auto spw1(std::make_shared<Widget>()); // make �Լ��� ���
std::shared_ptr<Widget> spw2(new Widget); // ������� ����



void processWidget(std::shared_ptr<Widget> spw, int priority) {}
int computePriority(void) {}



auto widgetDeleter = [](Widget* pw) {};
unique_ptr<Widget, decltype(widgetDeleter)>
upw(new Widget, widgetDeleter);

shared_ptr<Widget> spw(new Widget, widgetDeleter);



// std::initializer_list ��ü�� ����
auto initList = { 10, 20 };
// �� std::initializer_list ��ü�� �̿��ؼ� std::vector�� ����
auto spv = std::make_shared<std::vector<int>>(initList);



class ReallyBigType {};

// ���� ū ��ü�� std::make_shared�� �̿��ؼ� ����
auto pBigObj = std::make_shared<ReallyBigType>();



int main()
{
	// �ڿ� ���� ������ ����!
	processWidget(std::shared_ptr<Widget>(new Widget), computePriority());
	// �ڿ� ������ ������ ����
	processWidget(std::make_shared<Widget>(), computePriority());
	return 0;
}