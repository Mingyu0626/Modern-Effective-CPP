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
#include <list>
#include <regex>

using namespace std;

class Widget {};

int main()
{
	vector<string> vs;
	vs.push_back("xyzzy");
	vs.push_back(string("xyzzy")); // �ӽ� string ��ü�� �����ؼ� push_back�� ����



	vs.emplace_back("xyzzy"); // "xyzzy"�� �̿��ؼ� string�� vs �ȿ� ���� ����
	vs.emplace_back(50, 'x'); // 'x' ���� 50���� �̷���� string�� ����



	std::list<std::shared_ptr<Widget>> ptrs;
	// Ŀ���� ������
	void killWidget(Widget * pWidget);
	// ù��° ���
	ptrs.push_back(std::shared_ptr<Widget>(new Widget, killWidget));
	// �ι�° ���
	ptrs.push_back({ new Widget, killWidget });



	ptrs.emplace_back(new Widget, killWidget); // ���ܿ��� �������� ����

	std::shared_ptr<Widget> spw(new Widget, killWidget);
	// Widget ��ü��, �װ��� �����ϴ� spw ��ü�� ����
	ptrs.push_back(std::move(spw));

	std::shared_ptr<Widget> spw(new Widget, killWidget);
	// Widget ��ü��, �װ��� �����ϴ� spw ��ü�� ����
	ptrs.emplace_back(std::move(spw));



	std::vector<std::regex> regexes;

	regex r = nullptr; // ������ ����
	regexes.push_back(nullptr); // ������ ����

	regexes.emplace_back(nullptr);  // ������ ����
	regex r(nullptr) // ������ ����

	return 0;
}