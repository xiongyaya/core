
#include<ccdk/container/slist.h>
#include<stdio.h>
#include<string>

using namespace ccdk;
using namespace ccdk::mpl;
using namespace ccdk::ct;

void debug_slist()
{
	DebugNewTitle("ctor");
	{
		DebugSubTitle("default");
		{
			slist<int> s1{};
			slist<int> s2{ nullptr };
		}
		DebugSubTitle("fill ctor");
		{
			slist<int> s1{ 5, 1 };
			slist<std::string> s2{ 5, "hello" };
			s1.debug_value();
			s2.debug_value();
		}
		DebugSubTitle("range/range-n/array ctor");
		{
			slist<int> s1{ 5, 1 };
			slist<int> s2{ s1.begin(), s1.end() };
			slist<int> s3{ s1.cbegin(), s1.size() };
			s2.debug_value();
			s3.debug_value();
			slist<std::string> s4{ {"hello", "world", "c++"} };
			slist<std::string> s5{ s4.begin(), s4.end() };
			slist<std::string> s6{ s4.cbegin(), s4.cend() };
			s5.debug_value();
			s6.debug_value();
		}
		DebugSubTitle("copy/move ctor");
		{
			slist<int> s1{ 5, 2 };
			slist<int> s2{ s1 };
			slist<int> s3{ util::move(s1) };
			s1.debug_value();
			s2.debug_value();
			s3.debug_value();
			slist<std::string> s4{ { "hello", "world", "c++" } };
			slist<std::string> s5{ s4 };
			slist<std::string> s6{ util::move(s5) };
			s4.debug_value();
			s5.debug_value();
			s6.debug_value();
		}
		DebugSubTitle("swap");
		{
			slist<int> s1{ 5, 2 };
			slist<int> s2{ 5,1 };
			s1.debug_value();
			s2.debug_value();
			s1.swap(s2);
			s1.debug_value();
			s2.debug_value();
		}
	}
	DebugNewTitle("assign");
	{
		DebugSubTitle("copy/move assign");
		{
			slist<int> s1{ 5, 1 };
			slist<int> s2{ 3, 2 };
			slist<int> s3{ 6, 3 };
			slist<int> s4{ 10, 4 };
			s1.debug_value();
			s1 = s2;
			s1.debug_value();
			s1 = s3;
			s1.debug_value();
			s1 = util::move(s4);
			s4.debug_value();
			s1.debug_value();
			slist<std::string> s5{ 5, "hello" };
			slist<std::string> s6{ 3, "world" };
			slist<std::string> s7{ 6, "c++" };
			slist<std::string> s8{ 10, "java" };
			s5.debug_value();
			s5 = s6;
			s5.debug_value();
			s5 = s7;
			s5.debug_value();
			s5 = util::move(s8);
			s8.debug_value();
			s5.debug_value();
		}
		DebugSubTitle("assign fill");
		{
			slist<int> s1{ 5, 1 };
			s1.debug_value();
			s1.assign(3, 2);
			s1.debug_value();
			s1.assign(6, 3);
			s1.debug_value();
			slist<std::string> s2{ 5, "c++" };
			s2.debug_value();
			s2.assign(3, "java");
			s2.debug_value();
			s2.assign(6, "scala");
			s2.debug_value();
		}
		DebugSubTitle("assign array");
		{
			slist<int> s1{ 5, 1 };
			s1 = { 1,2,3,4,5 };
			s1.debug_value();
			slist<std::string> s2{ 5, "c++" };
			s2 = { "c++", "java", "scala", "python" };
			s2.debug_value();
		}
	}
	DebugNewTitle("it");
	{
		slist<int> s1{ { 1,2,3,4,5,4,3,2 } };
		ccdk_assert(s1.size() == 8);
		ccdk_assert(s1.begin() == s1.cbegin());
		slist<int>::const_iterator bg = s1.begin();
		for (auto &it : s1) {
			DebugValueIt(it);
		}
	}
	DebugNewTitle("pop/push");
	{
		slist<int> s1{ { 1,2,3,4,5,4,3,2 } };
		s1.pop_front();
		s1.debug_value();
		s1.push_front(3);
		s1.debug_value();
		s1.push_back(10);
		s1.debug_value();
		ccdk_assert(s1.back() == 10);
		ccdk_assert(s1.front() == 3);
	}
	DebugNewTitle("empty op");
	{
		{
			slist<int> s{};
			s.push_back(1);
		}
		{
			slist<int> s{};
			s.push_front(1);
		}
		{
			slist<int> s{};
			s = { 1,2,3,4 };
		}
		{
			slist<int> s{};
			s.pop_front();
		}
		{
			slist<int> s{ {1,2,3,4,5} };
			s.foreach([](int v) {
				DebugValueIt(v);
			});
			DebugValueItEnd();
		}
		{
			slist<int> s{ { 1,2,3,4,5 } };
			auto news = s.map([](int v) { return v + 3; });
			news.debug_value();
		}
	}
	DebugNewTitle("test que");
	{
		int i = 0; 
		slist<int> que;
		que.push_back(1);
		while (!que.empty() && i<5) {
			int top = que.front();
			que.pop_front();
			DebugValueIt(top);
			que.push_back(top * 2);
			que.push_back(top * 2 + 1);
			++i;
		}
	}
}

void debug_cached_slist()
{
	cached_slist<int> lst{ {1,2,3,4,5,6} };
	lst.pop_front();
	lst.pop_front();
	lst.push_front(2);
	lst.push_front(1);
	DebugValue("before destruct");
}

int main()
{
	debug_slist();
	debug_cached_slist();
	getchar();
	ccdk_open_leak_check();

	return 0;
}