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
	Widget(int i, double d); // 매개변수를 선언하지 않는
	Widget(std::initializer_list<long double> il);
	operator float(void) const; // float로 변환
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
//	Widget2(std::initializer_list<bool> il); // 이제는 요소의 타입이 bool
//};

class Widget2
{
public:
	Widget2(int i, bool b);
	Widget2(int i, double d);

	Widget2(std::initializer_list<string> il); // 이제는 요소의 타입이 string
};




int main()
{
	//int x = 0;
	//int y(0);
	//int z{ 0 };
	//int w = { 0 };

	double x, y, z;
	int sum1{ x + y + z }; // Error! double의 합을 int로 표현하지 못할 수 있음.
	int sum2(x + y + z); // OK(표현식의 값이 int에 맞게 잘려나감, 축소 변환이 일어남)
	int sum3 = x + y + z; // 마찬가지로 축소 변환 발생

	//Widget w1(10); // 인수 10으로 Widget의 생성자를 호출
	//Widget w2(); // 가장 성가신 구문 해석! Widget의 기본 생성자를 호출하는 것이 아니라, 
	//// Widget을 돌려주는, w2라는 이름의 함수를 선언한다
	//Widget w3{}; // 인수 없이 Widget의 생성자를 호출

	Widget w1(10, true); 
	Widget w2{ 10, true };
	Widget w3(10, 5.0); 
	Widget w4{ 10, 5.0 }; 

	Widget w5(w4); // 괄호 사용, 복사 생성자 호출
	Widget w6{ w4 }; // 중괄호 사용, std::initializer_list 생성자 호출
	// (w4가 float으로 변환되고 그 float이 long double로 변환됨)
	Widget w7(std::move(w4)); // 괄호 사용, 이동 생성자 호출
	Widget w8{ std::move(w4) }; // 중괄호 사용, std::initializer_list 생성자 호출
	// (w6에서와 마찬가지의 변환들이 일어남)



	Widget2 w1{ 10, 5.0 }; // Error! 축소 변환이 필요함

	Widget2 w2(10, true); // 괄호 사용, 여전히 첫 생성자를 호출
	Widget2 w3{ 10, true }; // 중괄호 사용, 이제는 첫 생성자 호출
	Widget2 w4(10, 5.0); // 괄호 사용, 여전히 둘째 생성자를 호출
	Widget2 w5{ 10, 5.0 }; // 중괄호 사용, 이제는 둘째 생성자 호출


	return 0;
}