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
bool highPriority = features(w)[5]; // w�� �켱������ ������?
processWidget(w, highPriority) // w�� �� �켱������ �°� ó��



int main()
{


	return 0;
}