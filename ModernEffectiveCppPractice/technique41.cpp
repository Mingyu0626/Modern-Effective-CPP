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
	void addName(string newName)
	{
		names.push_back(newName);
	}
private:
	vector<string> names;
};



// �����ε�
class Widget 
{
public:
	void addName(const string& newName)
	{
		names.push_back(newName);
	}

	void addName(std::string&& newName)
	{
		names.push_back(move(newName));
	}
private:
	vector<string> names;
};

// ���� ����
class Widget 
{
public:
	template<typename T>
	void addName(T&& newName)
	{
		names.push_back(forward<T>(newName));
	}
private:
	vector<string> names;
};

// �� ����
class Widget 
{
public:
	void addName(string newName)
	{
		names.push_back(move(newName));
	}
private:
	vector<string> names;
};



// addName�� �Ű������� names �����̳ʷ� �����ϱ� ����, �̸� ���̸� �����Ͽ�
// ���ǿ� ������ ������ �̸��� �߰�
int minLen = 3, maxLen = 10;
class Widget
{
public:
	void addName(string newName)
	{
		if (minLen <= newName.length() && newName.length() < maxLen)
		{
			names.push_back(move(newName));
		}
	}
private:
	vector<string> names;
};



class Password
{
public:
	explicit Password(string pwd)
		: text(move(pwd)) {} // �� ����, text�� �����Ѵ�.
	void changeTo(string newPwd)
	{
		text = move(newPwd); // �� ����, text�� �����Ѵ�.
	}

	void changeTo(const string& newPwd) // lvalue�� ���� �����ε� �Լ�
	{
		text = newPwd;
	}

private:
	string text;
};

int main()
{


	return 0;
}