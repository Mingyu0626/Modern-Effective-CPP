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

enum Color { black, white, red };
auto white = false;


enum class Color { black, white, red };
auto white = false;
// Color c = white;		// Error!
// Color c = Color::white; // OK


// ���� ������ int
enum class EStatus;

// ���� ���� ���� ����
enum class EStatus2 : std::uint32_t;
// ������ ���� ���� ����
enum class EStatus3 : std::uint32_t { a = 0 };

// ���� ���� enum ���� ���� ���� (���� ���� ������ ����)
enum EStatus4 : std::uint8_t;


int main()
{
	vector<size_t>primeFactors(size_t x);
	Color c = red;
	if (c < 14.5) // Color�� double�� ��..?
	{
		auto factors = primeFactors(c); // Color�� ���μ����� ���
	}


	vector<size_t>primeFactors(size_t x);
	Color c = Color::red;
	if (c < 14.5) // Error! Color�� double�� ���� �� ����
	{
		auto factors = primeFactors(c);
		// Error! Color ������ size_t�� �Ϲ������� ��ȯ�� �� ����
	}

	vector<size_t>primeFactors(size_t x);
	Color c = Color::red;
	if (static_cast<double>(c) < 14.5) // �̻��� �ڵ����� ��·�� ��ȿ
	{
		auto factors = primeFactors(static_cast<size_t>(c)); // �ǽɽ������� �������� ��
	}





	return 0;
}