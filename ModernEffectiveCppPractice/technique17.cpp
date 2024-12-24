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
#include <map>

using namespace std;

//class Widget 
//{
//public:
//	Widget(Widget&& rhs); // �̵� ������
//	Widget& operator=(Widget&& rhs); // �̵� ���� ������
//};



class Widget
{
public:
	~Widget();
	Widget(const Widget&) = default; // �⺻ ���� ������
	Widget& operator=(const Widget&) = default; // �⺻ ���� ���� ������
};



class Base
{
public:
	virtual ~Base() = default; // �Ҹ��ڸ� ��������
	Base(Base&&) = default; // �⺻ �̵� ������
	Base& operator=(Base&&) = default; // �⺻ �̵� ���� ������

	Base(const Base&) = default; // �⺻ ���� ������
	Base& operator=(const Base&) = default; // �⺻ ���� ���� ������
};



class StringTable
{
public:
	StringTable()
	{
		makeLogEntry("Creating StringTable object");
	}

	~StringTable()
	{
		makeLogEntry("Destroying StringTable object");
	}
private:
	map<int, string> values;
};

class Widget
{
	template<typename T>
	Widget(const T& rhs); // �� � �����ε� Widget�� ����

	template<typename T>
	Widget& operator=(const T& rhs); // �� � �����ε� Widget�� ���� ����(����)
};




int main()
{


	return 0;
}