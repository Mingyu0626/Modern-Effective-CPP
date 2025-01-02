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

class Widget {};


int computeImportantValue();


int main()
{
	atomic<int> ai(0); // ai를 0으로 초기화
	ai = 10; // 원자적으로 ai를 10으로 설정
	cout << ai; // 원자적으로 ai의 값을 출력
	++ai; // 원자적으로 ai 증가(11)
	--ai; // 원자적으로 ai 감소(10)

	volatile int vi(0); // vi를 0으로 초기화
	vi = 10; // vi를 10으로 설정
	std::cout << vi; // vi의 값을 읽기
	++vi; // vi를 증가
	--vi; // vi를 감소



	atomic<int> ac(0); // 원자적 카운터
	volatile int vc(0); // 휘발성 카운터



	atomic<bool> valAvailable(false);
	auto imptValue = computeImportantValue(); // 값을 계산한다.
	valAvailable = true; // 다른 과제에게 값이 준비되었음을 알린다.

	volatile bool valAvailable(false);
	auto imptValue = computeImportantValue();
	valAvailable = true;



	//int x;
	//auto y = x;
	//y = x;

	//volatile int x;
	//auto y = x;
	//y = x;

	//std::atomic<int> x; // 컴파일 Error 발생.
	//auto y = x;
	//y = x;
	//x = 10;
	//x = 20;


	atomic<int> x;
	atomic<int> y(x.load()); // x를 읽는다.
	y.store(x.load()); // x를 다시 읽는다.



	return 0;
}