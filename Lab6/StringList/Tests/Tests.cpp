#include "catch2/catch.hpp"
#include "StringList/StringList/CStringList.h"
#include <sstream>
#include <iostream>
#include <algorithm>
//iterator++ --
//print ss fun
//перемещение себя

TEST_CASE("CStringList() empty list")
{
	CStringList list1;
	CHECK(list1.Empty());
	CHECK(list1.Size() == 0);
	
}

TEST_CASE("CStringList(const CStringList& other);")
{
	std::stringstream ss;
	CStringList list1{ "a", "b", "c", "d" };
	CStringList list2(list1);
	for (auto item : list2)
	{
		ss << item;
	}
	for (auto item : list1)
	{
		ss << item;
	}
	CHECK(list2.Size() == 4);
	CHECK(ss.str() == "abcdabcd");
}

TEST_CASE("CStringList(CStringList&& other)")
{
	std::stringstream ss;
	CStringList list1{ "a", "b", "c", "d" };
	CStringList list2(std::move(list1));
	for (auto item : list2)
	{
		ss << item;
	}
	CHECK(list2.Size() == 4);
	CHECK(ss.str() == "abcd");
	CHECK(list1.Empty());
}

TEST_CASE("operator=(const CStringList& other)")
{
	std::stringstream ss;
	CStringList list1{ "a", "b", "c", "d" };
	CStringList list2{ "x", "y", "z" };
	list2 = list1;
	for (auto item : list2)
	{
		ss << item;
	}
	for (auto item : list1)
	{
		ss << item;
	}
	CHECK(list2.Size() == 4);
	CHECK(ss.str() == "abcdabcd");
}

TEST_CASE("operator=(CStringList&& other)")
{
	std::stringstream ss;
	CStringList list1{ "a", "b", "c", "d" };
	CStringList list2{ "x", "y", "z" };
	list2 = std::move(list1);
	for (auto item : list2)
	{
		ss << item;
	}
	CHECK(list2.Size() == 4);
	CHECK(ss.str() == "abcd");
	CHECK(list1.Empty());
}

TEST_CASE("PushFront()")
{
	std::stringstream ss;
	CStringList list1{ "a", "b", "c", "d" };
	list1.PushFront("x");
	CHECK(*list1.begin() == "x");
}

TEST_CASE("PushBack()")
{
	std::stringstream ss;
	CStringList list1{ "a", "b", "c", "d" };
	list1.PushBack("x");
	CHECK(*(--list1.end()) == "x");
}


TEST_CASE("Insert() in middle")
{
	std::stringstream ss;
	CStringList list1{ "a", "b", "c", "d" };
	auto it = list1.begin();
	it++;
	it++;
	list1.Insert(it, "f");
	for (auto item : list1)
	{
		ss << item;
	}
	CHECK(ss.str() == "abfcd");
}

TEST_CASE("Insert() in begin")
{
	std::stringstream ss;
	CStringList list1{ "a", "b", "c", "d" };
	auto it = list1.begin();
	list1.Insert(it, "f");
	for (auto item : list1)
	{
		ss << item;
	}
	CHECK(ss.str() == "fabcd");
}

TEST_CASE("Insert() in end")
{
	std::stringstream ss;
	CStringList list1{ "a", "b", "c", "d" };
	auto it = list1.end();
	list1.Insert(it, "f");
	for (auto item : list1)
	{
		ss << item;
	}
	CHECK(ss.str() == "abcdf");
}

TEST_CASE("Erase() ")
{
	std::stringstream ss;
	CStringList list1{ "a", "b", "c", "d" };
	auto it = list1.begin();
	it++;
	it++;
	list1.Erase(it);
	for (auto item : list1)
	{
		ss << item;
	}
	CHECK(ss.str() == "abd");
}

TEST_CASE("Erase() m_end")
{
	std::stringstream ss;
	CStringList list1{ "a", "b", "c", "d" };
	auto it = list1.end();
	CHECK_THROWS_AS(list1.Erase(it), std::invalid_argument);
}

TEST_CASE("clear")
{
	CStringList list1{ "a", "b", "c", "d" };
	list1.Clear();
	CHECK(list1.Size() == 0);
}

TEST_CASE("range based for")
{
	CStringList list1{ "a", "b", "c", "d" };
	std::stringstream ss;
	for (auto item : list1)
	{
		ss << item;
	}
	CHECK(ss.str() == "abcd");
}

TEST_CASE("STL algos")
{
	CStringList list1{ "a", "b", "c", "d" };
	std::reverse(list1.begin(), list1.end());
	std::stringstream ss;
	for (auto item : list1)
	{
		ss << item;
	}
	CHECK(ss.str() == "dcba");
}

TEST_CASE("reverse iterator")
{
	CStringList list1{ "a", "b", "c", "d" };
	std::stringstream ss;
	for (auto it = list1.rbegin(); it != list1.rend(); ++it)
	{
		ss << *it;
	}
	CHECK(ss.str() == "dcba");
}
