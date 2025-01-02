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



// 오버로딩
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

// 보편 참조
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

// 값 전달
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



// addName이 매개변수를 names 컨테이너로 복사하기 전에, 이름 길이를 점검하여
// 조건에 충족한 길이의 이름만 추가
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
		: text(move(pwd)) {} // 값 전달, text를 생성한다.
	void changeTo(string newPwd)
	{
		text = move(newPwd); // 값 전달, text를 대입한다.
	}

	void changeTo(const string& newPwd) // lvalue를 위한 오버로딩 함수
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