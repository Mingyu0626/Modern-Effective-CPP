#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <cassert>
#include <functional>
#include <new>

using namespace std;

class Widget {};

template<typename T>
class TD; // TD�� Type Displayer(���� ǥ�ñ�)�� ����

template<typename T> // ȣ���� ���ø� �Լ�
void f(const T& param) 
{
	cout << "T =     " << typeid(T).name() << "\n";
	cout << "param = " << typeid(param).name() << "\n";
}

vector<Widget> createVec() { return vector<Widget>(3, Widget()); } // ���丮 �Լ�

int main()
{
	const int theAnswer = 42;
	auto x = theAnswer;
	auto y = &theAnswer;
	// cout << typeid(x).name() << '\n';
	// cout << typeid(y).name() << '\n';

	const auto vw = createVec(); // vw�� ���丮 �Լ��� ��ȯ������ �ʱ�ȭ

	if (!vw.empty())
	{
		f(&vw[0]); // ���⼭ f�� ȣ��
	}


	return 0;
}