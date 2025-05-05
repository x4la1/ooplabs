#include <catch2/catch.hpp>
#include <iostream>
#include "String/String/String.h"
#include <sstream>

TEST_CASE("CMyString()")
{
	CMyString string;
	CHECK(string.GetCapacity() == 0);
	CHECK(string.GetLength() == 0);
	CHECK(string.GetStringData() == CMyString::s_empty);
}

TEST_CASE("CMyString(const char* pString)")
{
	const char* str = "abc";
	CMyString string(str);
	CHECK(string.GetCapacity() == 3);
	CHECK(string.GetLength() == 3);
	CHECK(std::equal(string.GetStringData(), string.GetStringData() + string.GetLength(), str));
}

TEST_CASE("CMyString(const char* pString) empty")
{
	const char* str = "";
	CMyString string(str);
	CHECK(string.GetCapacity() == 0);
	CHECK(string.GetLength() == 0);
	CHECK(string.GetStringData() == CMyString::s_empty);
}

TEST_CASE("CMyString(const char* pString, size_t length)")
{
	const char str[] = { 'a', 'b', '\0', 'c', 'd' };
	CMyString string(str, 5);
	CHECK(string.GetCapacity() == 5);
	CHECK(string.GetLength() == 5);
	CHECK(std::equal(string.GetStringData(), string.GetStringData() + string.GetLength(), str));
}

TEST_CASE("CMyString(const char* pString, size_t length) empty")
{
	const char str[1] = {};
	CMyString string(str, 0);
	CHECK(string.GetCapacity() == 0);
	CHECK(string.GetLength() == 0);
	CHECK(string.GetStringData() == CMyString::s_empty);
}

TEST_CASE("CMyString(std::string const& stlString)")
{
	std::string str = "abcabc";
	CMyString string(str);
	CHECK(string.GetCapacity() == 6);
	CHECK(string.GetLength() == 6);
	CHECK(std::equal(string.GetStringData(), string.GetStringData() + string.GetLength(), str.c_str()));
}

TEST_CASE("CMyString(std::string const& stlString) empty")
{
	std::string str = "";
	CMyString string(str);
	CHECK(string.GetCapacity() == 0);
	CHECK(string.GetLength() == 0);
	CHECK(string.GetStringData() == CMyString::s_empty);
}

TEST_CASE("CMyString(CMyString const& other)")
{
	const char* str = "asdasd";
	CMyString string(str);
	CMyString newString(string);
	CHECK(string.GetCapacity() == 6);
	CHECK(string.GetLength() == 6);
	CHECK(std::equal(string.GetStringData(), string.GetStringData() + string.GetLength(), str));
	CHECK(newString.GetCapacity() == 6);
	CHECK(newString.GetLength() == 6);
	CHECK(std::equal(newString.GetStringData(), newString.GetStringData() + newString.GetLength(), str));
}

TEST_CASE("CMyString(CMyString const& other) empty")
{
	const char* str = new char('\0');
	CMyString string(str);
	CMyString newString(string);
	CHECK(string.GetCapacity() == 0);
	CHECK(string.GetLength() == 0);
	CHECK(string.GetStringData() == CMyString::s_empty);
	CHECK(newString.GetCapacity() == 0);
	CHECK(newString.GetLength() == 0);
	CHECK(newString.GetStringData() == CMyString::s_empty);
}

TEST_CASE("CMyString(CMyString const& other) empty in middle")
{
	const char str[] = { 'a', 'b', '\0', 'c', 'd' };
	CMyString string(str, 5);
	CMyString newString(string);
	CHECK(string.GetCapacity() == 5);
	CHECK(string.GetLength() == 5);
	CHECK(std::equal(string.GetStringData(), string.GetStringData() + string.GetLength(), str));
	CHECK(newString.GetCapacity() == 5);
	CHECK(newString.GetLength() == 5);
	CHECK(std::equal(newString.GetStringData(), newString.GetStringData() + newString.GetLength(), str));
}

TEST_CASE("CMyString(CMyString&& other)")
{
	const char str[] = { 'a', 'b', 'c', 'd', '\0' };
	CMyString string(str, 5);
	CMyString newString(std::move(string));
	CHECK(string.GetCapacity() == 0);
	CHECK(string.GetLength() == 0);
	CHECK(string.GetStringData() == CMyString::s_empty);
	CHECK(newString.GetCapacity() == 5);
	CHECK(newString.GetLength() == 5);
	CHECK(std::equal(newString.GetStringData(), newString.GetStringData() + newString.GetLength(), str));
}

TEST_CASE("CMyString(CMyString&& other) empty")
{
	const char str[] = { '\0' };
	CMyString string(str);
	CMyString newString(std::move(string));
	CHECK(string.GetCapacity() == 0);
	CHECK(string.GetLength() == 0);
	CHECK(string.GetStringData() == CMyString::s_empty);
	CHECK(newString.GetCapacity() == 0);
	CHECK(newString.GetLength() == 0);
	CHECK(newString.GetStringData() == CMyString::s_empty);
}

TEST_CASE("CMyString(CMyString&& other) empty middle")
{
	const char str[] = { 'a', 'b', '\0', 'c', 'd' };
	CMyString string(str, 5);
	CMyString newString(std::move(string));
	CHECK(string.GetCapacity() == 0);
	CHECK(string.GetLength() == 0);
	CHECK(string.GetStringData() == CMyString::s_empty);
	CHECK(newString.GetCapacity() == 5);
	CHECK(newString.GetLength() == 5);
	CHECK(std::equal(newString.GetStringData(), newString.GetStringData() + newString.GetLength(), str));
}

TEST_CASE("GetStringData() - end == \0")
{
	CMyString str("abcdef");
	CHECK(*(str.GetStringData() + str.GetLength()) == '\0');
}


TEST_CASE("SubString() invalid 1")
{
	CMyString str("abcdef");
	CHECK_THROWS_AS(str.SubString(6, 5), std::out_of_range);
}

TEST_CASE("SubString() invalid 2")
{
	CMyString str("abcdef");
	CHECK_THROWS_AS(str.SubString(7, 5), std::out_of_range);
}

TEST_CASE("SubString() valid length in range")
{
	CMyString str("abcdef");
	CHECK(str.SubString(0, 6) == CMyString("abcdef"));
}

TEST_CASE("SubString() - valid length out of range")
{
	CMyString str("abcdef");
	CHECK(str.SubString(2, 150) == CMyString("cdef"));
}

TEST_CASE("Clear()")
{
	CMyString str("abcdef");
	str.Clear();
	CHECK(str.GetStringData() == CMyString::s_empty);
}

TEST_CASE("Clear() empty")
{
	CMyString str("");
	str.Clear();
	CHECK(str.GetStringData() == CMyString::s_empty);
}

TEST_CASE("operator=(const CMyString& other)")
{
	const char* str = "asdasd";
	CMyString string(str);
	CMyString newString = string;
	CHECK(string.GetCapacity() == 6);
	CHECK(string.GetLength() == 6);
	CHECK(std::equal(string.GetStringData(), string.GetStringData() + string.GetLength(), str));
	CHECK(newString.GetCapacity() == 6);
	CHECK(newString.GetLength() == 6);
	CHECK(std::equal(newString.GetStringData(), newString.GetStringData() + newString.GetLength(), str));

}

TEST_CASE("operator=(const CMyString& other) empty")
{
	const char* str = "";
	CMyString string(str);
	CMyString newString = string;
	CHECK(string.GetCapacity() == 0);
	CHECK(string.GetLength() == 0);
	CHECK(string.GetStringData() == CMyString::s_empty);
	CHECK(newString.GetCapacity() == 0);
	CHECK(newString.GetLength() == 0);
	CHECK(newString.GetStringData() == CMyString::s_empty);
}

TEST_CASE("operator=(const CMyString& other) middle empty")
{
	const char str[] = { 'a', 'b', '\0', 'c', 'd' };
	CMyString string(str, 5);
	CMyString newString = string;
	CHECK(string.GetCapacity() == 5);
	CHECK(string.GetLength() == 5);
	CHECK(std::equal(string.GetStringData(), string.GetStringData() + string.GetLength(), str));
	CHECK(newString.GetCapacity() == 5);
	CHECK(newString.GetLength() == 5);
	CHECK(std::equal(newString.GetStringData(), newString.GetStringData() + newString.GetLength(), str));
}

TEST_CASE("operator=(CMyString&& other)")
{
	const char* str = "asdasd";
	CMyString string(str);
	CMyString newString = std::move(string);
	CHECK(string.GetCapacity() == 0);
	CHECK(string.GetLength() == 0);
	CHECK(string.GetStringData() == CMyString::s_empty);
	CHECK(newString.GetCapacity() == 6);
	CHECK(newString.GetLength() == 6);
	CHECK(std::equal(newString.GetStringData(), newString.GetStringData() + newString.GetLength(), str));
}

TEST_CASE("operator=(CMyString&& other) empty")
{
	const char* str = "";
	CMyString string(str);
	CMyString newString = string;
	CHECK(string.GetCapacity() == 0);
	CHECK(string.GetLength() == 0);
	CHECK(string.GetStringData() == CMyString::s_empty);
	CHECK(newString.GetCapacity() == 0);
	CHECK(newString.GetLength() == 0);
	CHECK(newString.GetStringData() == CMyString::s_empty);
}

TEST_CASE("operator=(CMyString&& other) empty middle")
{
	const char str[] = { 'a', 'b', '\0', 'c', 'd' };
	CMyString string(str, 5);
	CMyString newString = std::move(string);
	CHECK(string.GetCapacity() == 0);
	CHECK(string.GetLength() == 0);
	CHECK(string.GetStringData() == CMyString::s_empty);
	CHECK(newString.GetCapacity() == 5);
	CHECK(newString.GetLength() == 5);
	CHECK(std::equal(newString.GetStringData(), newString.GetStringData() + newString.GetLength(), str));
}

TEST_CASE("operator+= other == epmty")
{
	const char* str = "abc";
	CMyString string1(str);
	CMyString string2("");
	string1 += string2;
	CHECK(string1 == CMyString("abc"));
	CHECK(string1.GetCapacity() == 3);
	CHECK(string1.GetLength() == 3);
}

TEST_CASE("operator+= capacity*2")
{
	const char* str = "abc";
	CMyString string1(str);
	CMyString string2("a");
	string1 += string2;
	CHECK(string1 == CMyString("abca"));
	CHECK(string1.GetCapacity() == 6);
	CHECK(string1.GetLength() == 4);
}

TEST_CASE("operator+= capacity > capacity * 2")
{
	const char* str = "abc";
	CMyString string1(str);
	CMyString string2("defg");
	string1 += string2;
	CHECK(string1 == CMyString("abcdefg"));
	CHECK(string1.GetCapacity() == 7);
	CHECK(string1.GetLength() == 7);
}

TEST_CASE("operator + CMyString")
{
	CMyString string1("abc");
	CMyString string2("defg");
	CMyString string3 = string1 + string2;
	CHECK(string3 == CMyString("abcdefg"));
	CHECK(string3.GetCapacity() == 7);
	CHECK(string3.GetLength() == 7);
}

TEST_CASE("operator + CMyString empty in middle")
{
	CMyString string1("a\0c", 3);
	CMyString string2("defg");
	CMyString string3 = string1 + string2;
	CHECK(string3 == CMyString("a\0cdefg", 7));
	CHECK(string3.GetCapacity() == 7);
	CHECK(string3.GetLength() == 7);
}

TEST_CASE("operator + stlString")
{
	CMyString string1("a\0c", 3);
	CMyString string2 = string1 + std::string("abs");
	CHECK(string2 == CMyString("a\0cabs", 6));
	CHECK(string2.GetCapacity() == 6);
	CHECK(string2.GetLength() == 6);
}

TEST_CASE("operator + char*")
{
	CMyString string1("a\0c", 3);
	CMyString string2 = string1 + "abs";
	CHECK(string2 == CMyString("a\0cabs", 6));
	CHECK(string2.GetCapacity() == 6);
	CHECK(string2.GetLength() == 6);
}

TEST_CASE("operator==  true")
{
	CMyString string1("abc");
	CMyString string2("abc");
	CHECK((string1 == string2) == true);
}

TEST_CASE("operator==  false")
{
	CMyString string1("abc");
	CMyString string2("abcd");
	CHECK((string1 == string2) == false);
}

TEST_CASE("operator!=  true")
{
	CMyString string1("abc");
	CMyString string2("abcd");
	CHECK((string1 != string2) == true);
}

TEST_CASE("operator!=  false")
{
	CMyString string1("abc");
	CMyString string2("abc");
	CHECK((string1 != string2) == false);
}

TEST_CASE("operator< right longer")
{
	CMyString string1("abc");
	CMyString string2("abcd");
	CHECK((string1 < string2) == true);
}

TEST_CASE("operator< ")
{
	CMyString string1("a");
	CMyString string2("b");
	CHECK((string1 < string2) == true);
}

TEST_CASE("operator< false")
{
	CMyString string1("a");
	CMyString string2("b");
	CHECK((string2 < string1) == false);
}

TEST_CASE("operator< equal")
{
	CMyString string1("a");
	CMyString string2("a");
	CHECK((string2 < string1) == false);
}

TEST_CASE("operator>>")
{
	std::string line = "abcef";
	std::stringstream ss(line);
	CMyString str;
	ss >> str;
	CHECK(str == CMyString("abcef"));
	CHECK(str.GetCapacity() == 5);
	CHECK(str.GetLength() == 5);
}

TEST_CASE("operator<< empty middle")
{
	std::stringstream ss;
	CMyString str("abc\0def", 7);
	ss << str;
	CHECK(CMyString(ss.str()) == str);
}

TEST_CASE("const char& operator[] - out of range")
{
	CMyString str("abc\0def", 7);
	CHECK_THROWS_AS(str[7], std::out_of_range);
}

TEST_CASE("const char& operator[] valid")
{
	CMyString str("abc\0def", 7);
	CHECK(str[3] == '\0');
}

TEST_CASE("char& operator[]")
{
	CMyString str("abc\0def", 7);
	str[3] = 'r';
	CHECK(str == CMyString("abcrdef"));
}