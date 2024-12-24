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
	template<typename T>
	void setName(T&& newName)
	{
		name = std::move(newName);
	}
private:
	string name;
	shared_ptr<string> p;
};

string getWidgetName() {} // ÆÑÅä¸® ÇÔ¼ö



template<typename T>
void setSignText(T&& text)
{
	sign.setText(text);

	auto now = chrono::system_clock::now();
	signHistory.add(now, std::forward<T>(text));
}



//class Matrix {};
//Matrix
//operator+(Matrix&& lhs, const Matrix& rhs)
//{
//	lhs += rhs;
//	return std::move(lhs);
//}
//
//Matrix
//operator+(Matrix&& lhs, const Matrix& rhs)
//{
//	lhs += rhs;
//	return lhs;
//}



int main()
{
	Widget w;
	auto n = getWidgetName();
	w.setName(n);

	return 0;
}