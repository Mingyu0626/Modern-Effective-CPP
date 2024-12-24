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

auto loggingDel = [](Widget* pw)
    {
        makeLogEntry(pw);
        delete pw;
    };

    // 삭제자의 타입이 포인터 타입의 일부임
unique_ptr<Widget, decltype(loggingDel)> upw(new Widget, loggingDel);

// 삭제자의 타입이 포인터 타입의 일부가 아님
shared_ptr<Widget> spw(new Widget, loggingDel);



auto customDeleter1 = [](Widget* pw) {}; // 커스텀 삭제자들, 형식은 서로 다르다.
auto customDeleter2 = [](Widget* pw) {};
shared_ptr<Widget> pw1(new Widget, customDeleter1);
shared_ptr<Widget> pw2(new Widget, customDeleter2);

vector<shared_ptr<Widget>> vpw{ pw1, pw2 };



// 매우 나쁜 설계 - raw Pointer로 여러개의 shared_ptr을 생성하는 방식
auto pw = new Widget; // pw는 생 포인터
std::shared_ptr<Widget> spw1(pw, loggingDel);
// *pw에 대한 제어 블록이 생성됨
std::shared_ptr<Widget> spw2(pw, loggingDel);
// *pw에 대한 두 번째 제어 블록이 생성됨



// 개선된 설계
std::shared_ptr<Widget> spw1(new Widget, loggingDel); // new를 직접 사용
std::shared_ptr<Widget> spw2(spw1); // spw2는 spw1과 동일한 제어 블록을 사용한다.



// shared_ptr를 이용한 Widget 객체 관리
vector<std::shared_ptr<Widget>> processedWidgets;
class Widget : enable_shared_from_this<Widget>
{
public:
    void process()
    {
        processedWidgets.emplace_back(shared_from_this()); 
    }
};


// 클라이언트의 객체 생성을 위한 팩토리 함수 + 
// 객체를 가리키는 shard_ptr가 외부에 없는 상황에서 shared_from_this 호출 방지 설계
class Widget : public std::enable_shared_from_this<Widget>
{
public:
    // 팩토리 함수; 인수들을 전용 생성자에 완벽하게 전달한다.
    template <typename... Ts>
    static std::shared_ptr<Widget> create(Ts&&... params);

    void process(void);
private:
    // 생성자들
};

int main()
{


	return 0;
}