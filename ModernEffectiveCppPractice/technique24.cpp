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

void f(Widget&& param); // rvalue ����
Widget&& var1 = Widget(); // rvalue ����
auto && var2 = var1; // ���� ����

template<typename T>
void f(vector<T>&& param); // rvalue ����

template<typename T>
void f(T&& param); // ���� ����


int main()
{

	return 0;
}