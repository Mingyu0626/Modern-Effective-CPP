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

enum Color { black, white, red };
auto white = false;


enum class Color { black, white, red };
auto white = false;
// Color c = white;		// Error!
// Color c = Color::white; // OK


// 바탕 형식은 int
enum class EStatus;

// 바탕 형식 새로 지정
enum class EStatus2 : std::uint32_t;
// 정의할 때도 지정 가능
enum class EStatus3 : std::uint32_t { a = 0 };

// 범위 없는 enum 바탕 형식 지정 (이제 전방 선언이 가능)
enum EStatus4 : std::uint8_t;


int main()
{
	vector<size_t>primeFactors(size_t x);
	Color c = red;
	if (c < 14.5) // Color와 double을 비교..?
	{
		auto factors = primeFactors(c); // Color의 소인수들을 계산
	}


	vector<size_t>primeFactors(size_t x);
	Color c = Color::red;
	if (c < 14.5) // Error! Color와 double을 비교할 수 없음
	{
		auto factors = primeFactors(c);
		// Error! Color 형식을 size_t로 암묵적으로 변환할 수 없음
	}

	vector<size_t>primeFactors(size_t x);
	Color c = Color::red;
	if (static_cast<double>(c) < 14.5) // 이상한 코드지만 어쨌든 유효
	{
		auto factors = primeFactors(static_cast<size_t>(c)); // 의심스럽지만 컴파일은 됨
	}





	return 0;
}