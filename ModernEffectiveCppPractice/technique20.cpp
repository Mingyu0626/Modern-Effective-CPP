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
#include <unordered_map>

using namespace std;

class Widget {};
class WidgetID {};



std::unique_ptr<const Widget> loadWidget(WidgetID id) {}

std::shared_ptr<const Widget> fastLoadWidget(WidgetID id)
{
	static std::unordered_map<WidgetID, std::weak_ptr<const Widget> > cache;

	// objPtr는 캐시에 있는 객체를 가리키는 std::shared_ptr
	// (단, 객체가 캐시에 없으면 널)
	auto objPtr = cache[id].lock();

	// 캐시에 없으면 적재하고 캐시에 저장
	if (!objPtr)
	{
		objPtr = loadWidget(id);
		cache[id] = objPtr;
	}

	return objPtr;
}


int main()
{
	// spw가 생성된 후, 피지칭 Widget의 참조 카운트(이하 간단히 카운트)는 1이다
	// (std::make_shared에 관해서는 항목 21을 보라).
	auto spw = std::make_shared<Widget>();
	// wpw는 spw와 같은 Widget을 가리킨다; 카운트는 여전히 1이다.
	std::weak_ptr<Widget> wpw(spw);
	// 카운트가 0이 되고 Widget이 파괴된다; 이제 wpw는 대상을 잃은 상태이다.
	spw = nullptr;



	// 방법 1 : lock 멤버 함수 사용
	std::shared_ptr<Widget> spw1 = wpw.lock(); // wpw가 만료이면 spw1은 널
	auto spw2 = wpw.lock(); // 위와 동일하나 auto를 사용했음

	// 방법 2 : shard_ptr의 생성자의 weak_ptr를 넘겨주기
	std::shared_ptr<Widget> spw3(wpw); // wpw가 만료이면 std::bad_weak_ptr(예외)가 발생

	return 0;
}