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
#include <list>
#include <regex>

using namespace std;

class Widget {};

int main()
{
	vector<string> vs;
	vs.push_back("xyzzy");
	vs.push_back(string("xyzzy")); // 임시 string 객체를 생성해서 push_back에 전달



	vs.emplace_back("xyzzy"); // "xyzzy"를 이용해서 string을 vs 안에 직접 생성
	vs.emplace_back(50, 'x'); // 'x' 문자 50개로 이루어진 string을 삽입



	std::list<std::shared_ptr<Widget>> ptrs;
	// 커스텀 삭제자
	void killWidget(Widget * pWidget);
	// 첫번째 방식
	ptrs.push_back(std::shared_ptr<Widget>(new Widget, killWidget));
	// 두번째 방식
	ptrs.push_back({ new Widget, killWidget });



	ptrs.emplace_back(new Widget, killWidget); // 예외에서 안전하지 않음

	std::shared_ptr<Widget> spw(new Widget, killWidget);
	// Widget 객체와, 그것을 관리하는 spw 객체를 생성
	ptrs.push_back(std::move(spw));

	std::shared_ptr<Widget> spw(new Widget, killWidget);
	// Widget 객체와, 그것을 관리하는 spw 객체를 생성
	ptrs.emplace_back(std::move(spw));



	std::vector<std::regex> regexes;

	regex r = nullptr; // 컴파일 에러
	regexes.push_back(nullptr); // 컴파일 에러

	regexes.emplace_back(nullptr);  // 컴파일 성공
	regex r(nullptr) // 컴파일 성공

	return 0;
}