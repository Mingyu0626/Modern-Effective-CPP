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
	bool isValidated() const;
	bool isProcessed() const;
	bool isArchived() const;

private:
	
};

// C++14
auto pw = make_unique<Widget>();
// 클로저의 자료 멤버를 std::move(pw)로 초기화한다.
auto func = [pw = move(pw)]
	{ return pw->isValidated() && pw->isArchived(); };

auto func = [pw = std::make_unique<Widget>()]
	{ return pw->isValidated()
	&& pw->isArchived(); };



// C++11
class IsValAndArch // 유효성 및 보관 여부를 판정하는 클래스
{
public:
	using DataType = unique_ptr<Widget>;

	explicit IsValAndArch(DataType&& ptr)
		: pw(move(ptr)) {}

	bool operator()() const
	{
		return pw->isValidated() && pw->isArchived();
	}

private:
	DataType pw;
};
auto func = IsValAndArch(make_unique<Widget>());



// C++14
auto func = [pw = std::make_unique<Widget>()]
	{ return pw->isValidated() && pw->isArchived(); };

// C++11
auto func = bind(
	[](const unique_ptr<Widget>& pw)
	{ return pw->isValidated() && pw->isArchived(); },
	make_unique<Widget>()
);

int main()
{
	vector<double> data;
	// C++14
	auto func = [data = std::move(data)]
		{};

	// C++11
	auto func =
		std::bind(
			[](const std::vector<double>& data)
			{},
			std::move(data)
		);




	return 0;
}