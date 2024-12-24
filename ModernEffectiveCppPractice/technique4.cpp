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
class TD; // TD는 Type Displayer(형식 표시기)의 약자

template<typename T> // 호출할 템플릿 함수
void f(const T& param) 
{
	cout << "T =     " << typeid(T).name() << "\n";
	cout << "param = " << typeid(param).name() << "\n";
}

vector<Widget> createVec() { return vector<Widget>(3, Widget()); } // 팩토리 함수

int main()
{
	const int theAnswer = 42;
	auto x = theAnswer;
	auto y = &theAnswer;
	// cout << typeid(x).name() << '\n';
	// cout << typeid(y).name() << '\n';

	const auto vw = createVec(); // vw를 팩토리 함수의 반환값으로 초기화

	if (!vw.empty())
	{
		f(&vw[0]); // 여기서 f를 호출
	}


	return 0;
}