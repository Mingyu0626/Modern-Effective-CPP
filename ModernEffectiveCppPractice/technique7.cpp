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

class Widget 
{
public:
	Widget(int i, bool b); // std::initializer_list
	Widget(int i, double d); // �Ű������� �������� �ʴ�
	Widget(std::initializer_list<long double> il);
	operator float(void) const; // float�� ��ȯ
private:
	int x{ 0 };
	int y = 0;
	// int z(0); // Error!
};

//class Widget2
//{
//public:
//	Widget2(int i, bool b);
//	Widget2(int i, double d);
//
//	Widget2(std::initializer_list<bool> il); // ������ ����� Ÿ���� bool
//};

class Widget2
{
public:
	Widget2(int i, bool b);
	Widget2(int i, double d);

	Widget2(std::initializer_list<string> il); // ������ ����� Ÿ���� string
};




int main()
{
	//int x = 0;
	//int y(0);
	//int z{ 0 };
	//int w = { 0 };

	double x, y, z;
	int sum1{ x + y + z }; // Error! double�� ���� int�� ǥ������ ���� �� ����.
	int sum2(x + y + z); // OK(ǥ������ ���� int�� �°� �߷�����, ��� ��ȯ�� �Ͼ)
	int sum3 = x + y + z; // ���������� ��� ��ȯ �߻�

	//Widget w1(10); // �μ� 10���� Widget�� �����ڸ� ȣ��
	//Widget w2(); // ���� ������ ���� �ؼ�! Widget�� �⺻ �����ڸ� ȣ���ϴ� ���� �ƴ϶�, 
	//// Widget�� �����ִ�, w2��� �̸��� �Լ��� �����Ѵ�
	//Widget w3{}; // �μ� ���� Widget�� �����ڸ� ȣ��

	Widget w1(10, true); 
	Widget w2{ 10, true };
	Widget w3(10, 5.0); 
	Widget w4{ 10, 5.0 }; 

	Widget w5(w4); // ��ȣ ���, ���� ������ ȣ��
	Widget w6{ w4 }; // �߰�ȣ ���, std::initializer_list ������ ȣ��
	// (w4�� float���� ��ȯ�ǰ� �� float�� long double�� ��ȯ��)
	Widget w7(std::move(w4)); // ��ȣ ���, �̵� ������ ȣ��
	Widget w8{ std::move(w4) }; // �߰�ȣ ���, std::initializer_list ������ ȣ��
	// (w6������ ���������� ��ȯ���� �Ͼ)



	Widget2 w1{ 10, 5.0 }; // Error! ��� ��ȯ�� �ʿ���

	Widget2 w2(10, true); // ��ȣ ���, ������ ù �����ڸ� ȣ��
	Widget2 w3{ 10, true }; // �߰�ȣ ���, ������ ù ������ ȣ��
	Widget2 w4(10, 5.0); // ��ȣ ���, ������ ��° �����ڸ� ȣ��
	Widget2 w5{ 10, 5.0 }; // �߰�ȣ ���, ������ ��° ������ ȣ��


	return 0;
}