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
	void addFilter() const;

private:
	int divisor;
};

using FilterContainer =
vector<function<bool(int)>>;

FilterContainer filters;

//void addDivisorFilter()
//{
//	auto calc1 = computeSomeValue1();
//	auto calc2 = computeSomeValue2();
//
//	auto divisor = computeDivisor(calc1, calc2);
//
//	filters.emplace_back(
//		[&](int value) { return value % divisor == 0; } // 위험하다.
//	);
//}

// 기본 참조 캡쳐 모드 사용
template<typename C>
void addDivisorFilter(const C& container)
{
	auto calc1 = computeSomeValue1();
	auto calc2 = computeSomeValue2();

	auto divisor = computeDivisor(calc1, calc2);

	using ContElemT = typename C::value_type; // 컨테이너에 담긴 요소들의 형식
	using std::begin;
	using std::end; // 일반성을 위한 using 사용, 항목13 참고

	if (std::all_of(
		begin(container), end(container),
		[&](const ContElemT& value)
		{ return value % divisor == 0; }) // 컨테이너의 모든 값이 divisor의 배수인가?
		)
	{
		// 그런 경우
	}
	else
	{
		// 아닌 경우
	}
}



// 기본 값 캡쳐 모드 사용
void addDivisorFilter()
{
	auto calc1 = computeSomeValue1();
	auto calc2 = computeSomeValue2();

	auto divisor = computeDivisor(calc1, calc2);

	filters.emplace_back(
		[=](int value) { return value % divisor == 0; } // 이제는 divisor가 대상을 잃지 않는다.
	);
}



// 기본 캡쳐 모드를 뜻하는 [=]의 = 제거
void Widget::addFilter() const
{
	filters.emplace_back(
		[](int value) { return value % divisor == 0; } // Error!
	);
}

// divisor를 명시적인 값으로 캡쳐
void Widget::addFilter() const
{
	filters.emplace_back(
		[divisor](int value)                           // Error!
		{ return value % divisor == 0; }
	);
}

// divisor를 지역 변수로 복사하여 해결
// C++11
void Widget::addFilter() const
{
	auto divisorCopy = divisor; // 자료 멤버를 복사
	filters.emplace_back(
		[divisorCopy](int value) // 복사본을 캡쳐
		{ return value % divisorCopy == 0; } // OK!
	);
}

// 기본 캡쳐 모드 사용, But 굳이 위험을 감수할 필요는 없음. 그냥 위에처럼 명시해주자.
void Widget::addFilter() const
{
	auto divisorCopy = divisor; // 자료 멤버를 복사
	filters.emplace_back(
		[=](int value) // 복사본을 캡쳐
		{ return value % divisorCopy == 0; } // OK!
	);
}

// C++14
void Widget::addFilter() const
{
	filters.emplace_back(
		[divisor = divisor](int value) // divisor를 클로저에 복사
		{ return value % divisor == 0; } // OK!
	);
}



// static 변수를 사용한 예시
void addDivisorFilter()
{
	static auto calc1 = computeSomeValue1();
	static auto calc2 = computeSomeValue2();

	static auto divisor =
		computeDivisor(calc1, calc2);

	filters.emplace_back(
		[=](int value) // 아무 것도 캡쳐하지 않는다.
		{ return value % divisor == 0; } // 위 정적 변수 divisor를 지칭한다.
	);

	++divisor; // divisor를 수정한다.
}

int main()
{


	return 0;
}