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
using namespace std::placeholders; // _1�� ����ϴµ� �ʿ�

class Widget {};

using Time = std::chrono::steady_clock::time_point; // �׸�9 ����

enum class Sound { Beep, Siren, Whistle }; // �׸�10 ����

using Duration = std::chrono::steady_clock::duration;

void setAlarm(Time t, Sound s, Duration d) {}

// C++14, ���ٸ� ����� ����
auto setSoundL =
[](Sound s)
    {
        setAlarm(steady_clock::now() + 1h, s, 30s);
        // 1�ð� �ĺ��� ������ �溸���� 30�ʰ� ���
    };

// ȣ�� ������ ���� �߻�. ���� �Լ��� ȣ�� ����(steady_clock::now())�� �ٸ�
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



// �����ε� ���� �߻�. �Ʒ� �����ε� ������ �����, bind�� ����� ������ ��� ������ ���� �߻�
// void setAlarm(Time t, Sound s, Duration d, Volume v) {}

using SetAlram3ParamType = void(*)(Time t, Sound s, Duration d);
auto setSoundB =
std::bind(static_cast<SetAlram3ParamType>(setAlarm),
    std::bind(std::plus<>(),
        std::bind(steady_clock::now),
        1h),
    _1,
    30s);



// ������ ������ ����, Widget ��ü�� ���� ���纻�� ����� �Լ�
enum class CompLevel { Low, Normal, High };
Widget compress(const Widget& w, CompLevel lev) {}
Widget w;

// C++14 ���ε� ����
auto compressRateB = std::bind(compress, w, _1);



// C++11, ���ε带 ����ؾ� �ϴ� ��� ����, ������ �Լ� ��ü
class PolyWidget 
{
public:
    template<typename T>
    void operator()(const T& param) const;
};


int main()
{
    // ���� �� �������� ����.

    // C++14 ���� ����
    int lowVal, highVal;
    auto betweenL =
        [lowVal, highVal]
        (const auto& val)
        { return lowVal <= val && val <= highVal; };

    // C++14 ���ε� ����
    auto betweenB =
        std::bind(std::logical_and<>(),
            std::bind(std::less_equal<>(), lowVal, _1),
            std::bind(std::less_equal<>(), _1, highVal));



    // C++14 ���� ����
    Widget w;
    auto compressRateL = // w�� ������ ĸ�ĵǰ�, lev�� ������ ���޵ȴ�.
        [w](CompLevel lev)
        { return compress(w, lev); };



    // C++11���� ���ε带 ����ؾ� �� ��� ����, ������ �Լ� ��ü
    PolyWidget pw;
    auto boundPW = std::bind(pw, _1);
    boundPW(1930);
    boundPW(nullptr);
    boundPW("Rosebud");

    // C++14, ���ε� ��� ���� auto �Ű������� ���� ���ٷ� ������ ���� ����
    auto boundPW = [pw](const auto& param)
        { pw(param); };


	return 0;
}