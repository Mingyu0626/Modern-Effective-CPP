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

void f(Widget&& param); // rvalue 참조
Widget&& var1 = Widget(); // rvalue 참조
auto && var2 = var1; // 보편 참조

template<typename T>
void f(vector<T>&& param); // rvalue 참조

template<typename T>
void f(T&& param); // 보편 참조


int main()
{

	return 0;
}