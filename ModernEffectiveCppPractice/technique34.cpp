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
using namespace std::chrono;
using namespace std::literals;
using namespace std::placeholders; // _1을 사용하는데 필요

class Widget {};

using Time = std::chrono::steady_clock::time_point; // 항목9 참고

enum class Sound { Beep, Siren, Whistle }; // 항목10 참고

using Duration = std::chrono::steady_clock::duration;

void setAlarm(Time t, Sound s, Duration d) {}

// C++14, 람다를 사용한 버전
auto setSoundL =
[](Sound s)
    {
        setAlarm(steady_clock::now() + 1h, s, 30s);
        // 1시간 후부터 지정된 경보음을 30초간 재생
    };

// 호출 시점의 문제 발생. 람다 함수와 호출 시점(steady_clock::now())이 다름
auto setSoundB =
std::bind(setAlarm,steady_clock::now() + 1h, _1, 30s);


// C++14 
auto setsoundB =
std::bind(setAlarm,
    std::bind(std::plus<>(),
        std::bind(steady_clock::now), 1h), _1, 30s);

// C++11
auto setsoundB =
std::bind(setAlarm,
    std::bind(std::plus<steady_clock::time_point>(),
        std::bind(steady_clock::now), hours(1)),
    _1, seconds(30));



// 오버로딩 문제 발생. 아래 오버로딩 버전을 만들면, bind를 사용한 버전의 경우 컴파일 오류 발생
// void setAlarm(Time t, Sound s, Duration d, Volume v) {}

using SetAlram3ParamType = void(*)(Time t, Sound s, Duration d);
auto setSoundB =
std::bind(static_cast<SetAlram3ParamType>(setAlarm),
    std::bind(std::plus<>(),
        std::bind(steady_clock::now),
        1h),
    _1,
    30s);



// 참조와 복사의 문제, Widget 객체의 압축 복사본을 만드는 함수
enum class CompLevel { Low, Normal, High };
Widget compress(const Widget& w, CompLevel lev) {}
Widget w;

// C++14 바인드 버전
auto compressRateB = std::bind(compress, w, _1);



// C++11, 바인드를 사용해야 하는 경우 예제, 다형적 함수 객체
class PolyWidget 
{
public:
    template<typename T>
    void operator()(const T& param) const;
};


int main()
{
    // 구현 및 유지보수 문제.

    // C++14 람다 버전
    int lowVal, highVal;
    auto betweenL =
        [lowVal, highVal]
        (const auto& val)
        { return lowVal <= val && val <= highVal; };

    // C++14 바인드 버전
    auto betweenB =
        std::bind(std::logical_and<>(),
            std::bind(std::less_equal<>(), lowVal, _1),
            std::bind(std::less_equal<>(), _1, highVal));



    // C++14 람다 버전
    Widget w;
    auto compressRateL = // w는 값으로 캡쳐되고, lev는 값으로 전달된다.
        [w](CompLevel lev)
        { return compress(w, lev); };



    // C++11에서 바인드를 사용해야 할 경우 예제, 다형적 함수 객체
    PolyWidget pw;
    auto boundPW = std::bind(pw, _1);
    boundPW(1930);
    boundPW(nullptr);
    boundPW("Rosebud");

    // C++14, 바인드 사용 없이 auto 매개변수를 가진 람다로 간단히 구현 가능
    auto boundPW = [pw](const auto& param)
        { pw(param); };


	return 0;
}