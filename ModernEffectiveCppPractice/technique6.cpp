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

vector<bool> features(const Widget& w); 
Widget w;
bool highPriority = features(w)[5]; // w의 우선순위가 높은가?
processWidget(w, highPriority) // w를 그 우선순위에 맞게 처리



int main()
{


	return 0;
}