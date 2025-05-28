#include "catch2/catch.hpp"
#include <iostream>
#include "MyArray/MyArray/MyArray.h"
#include <sstream>
#include <string>

TEST_CASE("MyArray()")
{
	MyArray<double> arr;
	CHECK(arr.Size() == 0);
}

TEST_CASE("MyArray(const MyArray& other)")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	MyArray<double> arr2(arr);
	CHECK(arr2.Size() == 4);
	CHECK(arr2[0] == 2.0);
	CHECK(arr2[1] == 3.0);
	CHECK(arr2[2] == 4.0);
	CHECK(arr2[3] == 5.0);
}

TEST_CASE("MyArray(MyArray&& other)")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	MyArray<double> arr2(std::move(arr));
	CHECK(arr2.Size() == 4);
	CHECK(arr2[0] == 2.0);
	CHECK(arr2[1] == 3.0);
	CHECK(arr2[2] == 4.0);
	CHECK(arr2[3] == 5.0);
	CHECK(arr.Size() == 0);
}

TEST_CASE("operator=(const MyArray& other) this = other")
{
	MyArray<double> arr2;
	arr2.PushBack(2.0);
	arr2.PushBack(3.0);
	arr2.PushBack(4.0);
	arr2.PushBack(5.0);
	arr2 = arr2;
	CHECK(arr2.Size() == 4);
	CHECK(arr2[0] == 2.0);
	CHECK(arr2[1] == 3.0);
	CHECK(arr2[2] == 4.0);
	CHECK(arr2[3] == 5.0);
}

TEST_CASE("operator=(const MyArray& other)")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	MyArray<double> arr2 = arr; 
	CHECK(arr2.Size() == 4);
	CHECK(arr2[0] == 2.0);
	CHECK(arr2[1] == 3.0);
	CHECK(arr2[2] == 4.0);
	CHECK(arr2[3] == 5.0);
}

TEST_CASE("operator=(MyArray&& other) this = other")
{
	MyArray<double> arr2;
	arr2.PushBack(2.0);
	arr2.PushBack(3.0);
	arr2.PushBack(4.0);
	arr2.PushBack(5.0);
	arr2 = std::move(arr2);
	CHECK(arr2.Size() == 4);
	CHECK(arr2[0] == 2.0);
	CHECK(arr2[1] == 3.0);
	CHECK(arr2[2] == 4.0);
	CHECK(arr2[3] == 5.0);
}

TEST_CASE("operator=(MyArray&& other) ")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	MyArray<double> arr2 = std::move(arr);
	CHECK(arr2.Size() == 4);
	CHECK(arr2[0] == 2.0);
	CHECK(arr2[1] == 3.0);
	CHECK(arr2[2] == 4.0);
	CHECK(arr2[3] == 5.0);
	CHECK(arr.Size() == 0);
}

TEST_CASE("T& operator[] out of range")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	CHECK_THROWS_AS(arr[4], std::out_of_range);
}

TEST_CASE("T& operator[] valid")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr[0] = 0.0;
	arr[3] = 6.0;
	CHECK(arr.Size() == 4);
	CHECK(arr[0] == 0.0);
	CHECK(arr[1] == 3.0);
	CHECK(arr[2] == 4.0);
	CHECK(arr[3] == 6.0);
}

TEST_CASE("const T& operator[]")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	const MyArray<double> arr2 = arr;
	const double num = arr2[3]; 
	CHECK(arr.Size() == 4);
	CHECK(num == 5.0);
}

TEST_CASE("Resize >")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.Resize(10);
	CHECK(arr.Size() == 10);
	CHECK(arr[9] == 0.0);
	CHECK_THROWS_AS(arr[10], std::out_of_range);
}

TEST_CASE("Resize <")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	arr.Resize(2);
	CHECK(arr.Size() == 2);
	CHECK(arr[0] == 2.0);
	CHECK(arr[1] == 3.0);
	CHECK_THROWS_AS(arr[3], std::out_of_range);
}

TEST_CASE("Clear()")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	arr.Clear();
	CHECK(arr.Size() == 0);
	CHECK_THROWS_AS(arr[0], std::out_of_range);
}

TEST_CASE("Iterator++ out of range")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	CHECK_THROWS_AS(arr.end()++, std::out_of_range);
}

TEST_CASE("Iterator-- out of range")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	CHECK_THROWS_AS(arr.begin()--, std::out_of_range);
}

TEST_CASE("Iterator+= out of range")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	CHECK_THROWS_AS(arr.end()+= 1, std::out_of_range);
}

TEST_CASE("Iterator-= out of range")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	CHECK_THROWS_AS(arr.begin() -= 1, std::out_of_range);
}

TEST_CASE("Iterator - n out of range")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	CHECK_THROWS_AS(arr.begin() - 1, std::out_of_range);
}

TEST_CASE("Iterator + n out of range")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	CHECK_THROWS_AS(arr.end() + 1, std::out_of_range);
}

TEST_CASE("++Iterator valid")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	CHECK(*(++arr.begin()) == 3.0);
}

TEST_CASE("Iterator++ valid")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	CHECK(*(arr.begin()++) == 2.0);
}

TEST_CASE("Iterator + n valid")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	CHECK(*(arr.begin() + 5) == 7.0);
}

TEST_CASE("Iterator - n valid")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	CHECK(*(arr.end() - 5) == 4.0);
}

TEST_CASE("Iterator ==")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	CHECK((arr.end() == arr.end()) == true);
}

TEST_CASE("Iterator !=")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	CHECK((arr.begin() == arr.end()) == false);
}

TEST_CASE("Iterator <")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	CHECK((arr.begin() < arr.end()) == true);
}

TEST_CASE("Iterator >")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	CHECK((arr.end() > arr.begin()) == true);
}

TEST_CASE("range based for")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	std::stringstream ss;
	for (auto elem: arr)
	{
		ss << elem;
	}
	CHECK(ss.str() == "2345678");
}

TEST_CASE("reverse range based for")
{
	MyArray<double> arr;
	arr.PushBack(2.0);
	arr.PushBack(3.0);
	arr.PushBack(4.0);
	arr.PushBack(5.0);
	arr.PushBack(6.0);
	arr.PushBack(7.0);
	arr.PushBack(8.0);
	std::stringstream ss;
	for (auto it = arr.rbegin(); it != arr.rend(); ++it)
	{
		ss << *it;
	}
	CHECK(ss.str() == "8765432");
}

TEST_CASE("STL functions")
{
	MyArray<double> arr;
	arr.PushBack(8.0);
	arr.PushBack(7.0);
	arr.PushBack(6.0);
	arr.PushBack(5.0);
	arr.PushBack(4.0);
	arr.PushBack(3.0);
	arr.PushBack(2.0);
	std::sort(arr.begin(), arr.end());
	std::stringstream ss;
	for (auto elem : arr)
	{
		ss << elem;
	}
	CHECK(ss.str() == "2345678");
}

TEST_CASE("MyArray<std::string> 1")
{
	MyArray<std::string> arr{};
	arr.PushBack("abc");
	arr.PushBack("qwe");
	arr.PushBack("asd");
	arr.PushBack("zxcvbn");
	arr.Resize(10);
	arr.PushBack("denis");
	CHECK(arr[0] == "abc");
	CHECK(arr[1] == "qwe");
	CHECK(arr[2] == "asd");
	CHECK(arr[3] == "zxcvbn");
	CHECK(arr[10] == "denis");
}

TEST_CASE("MyArray<std::string> copy")
{
	MyArray<std::string> arr{};
	arr.PushBack("abc");
	arr.PushBack("qwe");
	arr.PushBack("asd");
	arr.PushBack("zxcvbn");
	arr.Resize(10);
	arr.PushBack("denis");
	MyArray<std::string> arr2 = arr;
	CHECK(arr2[0] == "abc");
	CHECK(arr2[1] == "qwe");
	CHECK(arr2[2] == "asd");
	CHECK(arr2[3] == "zxcvbn");
	CHECK(arr2[10] == "denis");
}

TEST_CASE("MyArray<std::string> = move")
{
	MyArray<std::string> arr{};
	arr.PushBack("abc");
	arr.PushBack("qwe");
	arr.PushBack("asd");
	arr.PushBack("zxcvbn");
	arr.Resize(10);
	arr.PushBack("denis");
	MyArray<std::string> arr2 = std::move(arr);
	CHECK(arr2[0] == "abc");
	CHECK(arr2[1] == "qwe");
	CHECK(arr2[2] == "asd");
	CHECK(arr2[3] == "zxcvbn");
	CHECK(arr2[10] == "denis");
	CHECK(arr.Size() == 0);
}

TEST_CASE("MyArray<std::string> []")
{
	MyArray<std::string> arr{};
	arr.PushBack("abc");
	arr.PushBack("qwe");
	arr.PushBack("asd");
	arr.PushBack("zxcvbn");
	arr.Resize(10);
	arr.PushBack("denis");
	MyArray<std::string> arr2 = std::move(arr);
	arr2[0] += "abc";
	CHECK(arr2[0] == "abcabc");
	CHECK(arr2[1] == "qwe");
	CHECK(arr2[2] == "asd");
	CHECK(arr2[3] == "zxcvbn");
	CHECK(arr2[10] == "denis");
}