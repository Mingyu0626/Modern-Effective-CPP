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

auto loggingDel = [](Widget* pw)
    {
        makeLogEntry(pw);
        delete pw;
    };

    // �������� Ÿ���� ������ Ÿ���� �Ϻ���
unique_ptr<Widget, decltype(loggingDel)> upw(new Widget, loggingDel);

// �������� Ÿ���� ������ Ÿ���� �Ϻΰ� �ƴ�
shared_ptr<Widget> spw(new Widget, loggingDel);



auto customDeleter1 = [](Widget* pw) {}; // Ŀ���� �����ڵ�, ������ ���� �ٸ���.
auto customDeleter2 = [](Widget* pw) {};
shared_ptr<Widget> pw1(new Widget, customDeleter1);
shared_ptr<Widget> pw2(new Widget, customDeleter2);

vector<shared_ptr<Widget>> vpw{ pw1, pw2 };



// �ſ� ���� ���� - raw Pointer�� �������� shared_ptr�� �����ϴ� ���
auto pw = new Widget; // pw�� �� ������
std::shared_ptr<Widget> spw1(pw, loggingDel);
// *pw�� ���� ���� ����� ������
std::shared_ptr<Widget> spw2(pw, loggingDel);
// *pw�� ���� �� ��° ���� ����� ������



// ������ ����
std::shared_ptr<Widget> spw1(new Widget, loggingDel); // new�� ���� ���
std::shared_ptr<Widget> spw2(spw1); // spw2�� spw1�� ������ ���� ����� ����Ѵ�.



// shared_ptr�� �̿��� Widget ��ü ����
vector<std::shared_ptr<Widget>> processedWidgets;
class Widget : enable_shared_from_this<Widget>
{
public:
    void process()
    {
        processedWidgets.emplace_back(shared_from_this()); 
    }
};


// Ŭ���̾�Ʈ�� ��ü ������ ���� ���丮 �Լ� + 
// ��ü�� ����Ű�� shard_ptr�� �ܺο� ���� ��Ȳ���� shared_from_this ȣ�� ���� ����
class Widget : public std::enable_shared_from_this<Widget>
{
public:
    // ���丮 �Լ�; �μ����� ���� �����ڿ� �Ϻ��ϰ� �����Ѵ�.
    template <typename... Ts>
    static std::shared_ptr<Widget> create(Ts&&... params);

    void process(void);
private:
    // �����ڵ�
};

int main()
{


	return 0;
}