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


int computeImportantValue();


int main()
{
	atomic<int> ai(0); // ai�� 0���� �ʱ�ȭ
	ai = 10; // ���������� ai�� 10���� ����
	cout << ai; // ���������� ai�� ���� ���
	++ai; // ���������� ai ����(11)
	--ai; // ���������� ai ����(10)

	volatile int vi(0); // vi�� 0���� �ʱ�ȭ
	vi = 10; // vi�� 10���� ����
	std::cout << vi; // vi�� ���� �б�
	++vi; // vi�� ����
	--vi; // vi�� ����



	atomic<int> ac(0); // ������ ī����
	volatile int vc(0); // �ֹ߼� ī����



	atomic<bool> valAvailable(false);
	auto imptValue = computeImportantValue(); // ���� ����Ѵ�.
	valAvailable = true; // �ٸ� �������� ���� �غ�Ǿ����� �˸���.

	volatile bool valAvailable(false);
	auto imptValue = computeImportantValue();
	valAvailable = true;



	//int x;
	//auto y = x;
	//y = x;

	//volatile int x;
	//auto y = x;
	//y = x;

	//std::atomic<int> x; // ������ Error �߻�.
	//auto y = x;
	//y = x;
	//x = 10;
	//x = 20;


	atomic<int> x;
	atomic<int> y(x.load()); // x�� �д´�.
	y.store(x.load()); // x�� �ٽ� �д´�.



	return 0;
}