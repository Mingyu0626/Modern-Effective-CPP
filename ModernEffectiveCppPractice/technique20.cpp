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
class WidgetID {};



std::unique_ptr<const Widget> loadWidget(WidgetID id) {}

std::shared_ptr<const Widget> fastLoadWidget(WidgetID id)
{
	static std::unordered_map<WidgetID, std::weak_ptr<const Widget> > cache;

	// objPtr�� ĳ�ÿ� �ִ� ��ü�� ����Ű�� std::shared_ptr
	// (��, ��ü�� ĳ�ÿ� ������ ��)
	auto objPtr = cache[id].lock();

	// ĳ�ÿ� ������ �����ϰ� ĳ�ÿ� ����
	if (!objPtr)
	{
		objPtr = loadWidget(id);
		cache[id] = objPtr;
	}

	return objPtr;
}


int main()
{
	// spw�� ������ ��, ����Ī Widget�� ���� ī��Ʈ(���� ������ ī��Ʈ)�� 1�̴�
	// (std::make_shared�� ���ؼ��� �׸� 21�� ����).
	auto spw = std::make_shared<Widget>();
	// wpw�� spw�� ���� Widget�� ����Ų��; ī��Ʈ�� ������ 1�̴�.
	std::weak_ptr<Widget> wpw(spw);
	// ī��Ʈ�� 0�� �ǰ� Widget�� �ı��ȴ�; ���� wpw�� ����� ���� �����̴�.
	spw = nullptr;



	// ��� 1 : lock ��� �Լ� ���
	std::shared_ptr<Widget> spw1 = wpw.lock(); // wpw�� �����̸� spw1�� ��
	auto spw2 = wpw.lock(); // ���� �����ϳ� auto�� �������

	// ��� 2 : shard_ptr�� �������� weak_ptr�� �Ѱ��ֱ�
	std::shared_ptr<Widget> spw3(wpw); // wpw�� �����̸� std::bad_weak_ptr(����)�� �߻�

	return 0;
}