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

template<typename C, typename V>
void findAndInsert(C& container, const V& targetVal, const V& inserVal)
{
	using std::cbegin;
	using std::cend;
	auto it = find(cbegin(container), cend(container), targetVal);
	// container���� targetVal�� ù ���� ��ġ�� ã�´�.

	container.insert(it, insertVal);
	// �� ��ġ�� insertVal�� �����Ѵ�.
}

template <class C>
auto cbegin(const C& container) -> decltype(begin(container))
{
	return begin(container);
}



int main()
{
	vector<int> values;
	auto it = find(values.cbegin(), values.cend(), 1983);
	values.insert(it, 1988);
	return 0;
}