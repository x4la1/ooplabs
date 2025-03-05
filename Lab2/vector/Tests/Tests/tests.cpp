#include "../vector/vector.h"
#include <catch2/catch.hpp>
#include <sstream>

TEST_CASE("ReadNumbers() - Empty input")
{
	std::istringstream iss(""); //пустая строка
	std::cin.rdbuf(iss.rdbuf());
	std::vector<double> result = ReadNumbers();
	CHECK(result.empty());
}

TEST_CASE("ReadNumbers() - Valid input")
{
	std::istringstream iss1("1 2 3"); //положительные целые числа
	std::cin.rdbuf(iss1.rdbuf());
	std::vector<double> result1 = ReadNumbers();
	CHECK(result1 == std::vector<double>{ 1, 2, 3 });

	std::istringstream iss2("4 16 -30 10"); //+отрицательные целые числа
	std::cin.rdbuf(iss2.rdbuf());
	std::vector<double> result2 = ReadNumbers();
	CHECK(result2 == std::vector<double>{ 4, 16, -30, 10 });

	std::istringstream iss3("-1.0004000 -703 3.659512 -11"); // положительные и отрицательные с плавающей точкой
	std::cin.rdbuf(iss3.rdbuf());
	std::vector<double> result3 = ReadNumbers();
	CHECK(result3 == std::vector<double>{ -1.0004000, -703, 3.659512, -11 });
}

TEST_CASE("ReadNumbers() - Invalid input")
{
	std::istringstream iss1("1 a 3"); //недопустимые символы
	std::cin.rdbuf(iss1.rdbuf());
	CHECK_THROWS_AS(ReadNumbers(), std::invalid_argument);

	std::istringstream iss2("1a 2 3"); //недопустимые символы
	std::cin.rdbuf(iss2.rdbuf());
	CHECK_THROWS_AS(ReadNumbers(), std::invalid_argument);

	std::istringstream iss3("01 2 3"); //неверные числа
	std::cin.rdbuf(iss3.rdbuf());
	CHECK_THROWS_AS(ReadNumbers(), std::invalid_argument);

	std::istringstream iss4(".1 2 3"); //неверные числа
	std::cin.rdbuf(iss4.rdbuf());
	CHECK_THROWS_AS(ReadNumbers(), std::invalid_argument);

	std::istringstream iss5("01 2 3"); //неверные числа
	std::cin.rdbuf(iss5.rdbuf());
	CHECK_THROWS_AS(ReadNumbers(), std::invalid_argument);

	std::istringstream iss6("-.1 2 3"); //неверные числа
	std::cin.rdbuf(iss6.rdbuf());
	CHECK_THROWS_AS(ReadNumbers(), std::invalid_argument);

	std::istringstream iss7("0.-1 2 3"); //неверные числа
	std::cin.rdbuf(iss7.rdbuf());
	CHECK_THROWS_AS(ReadNumbers(), std::invalid_argument);
}

TEST_CASE("ProcessNumbers()")
{
	std::vector<double> result1 = ProcessNumbers(std::vector<double>{ 1, 2, 3 }); //целые положительные числа
	CHECK(result1 == std::vector<double>{ 3, 4, 5 });

	std::vector<double> result2 = ProcessNumbers(std::vector<double>{ 1.0, 2, 3.63 }); //положительные с плавающей точкой
	CHECK(result2 == std::vector<double>{ 3.21, 4.21, 5.84 });

	std::vector<double> result3 = ProcessNumbers(std::vector<double>{ -1, -3, -3.62 }); //отрицательные с плавающей точкой
	CHECK(result3 == std::vector<double>{ -1, -3, -3.62 });

	std::vector<double> result4 = ProcessNumbers(std::vector<double>{ -2, 1, 3 }); //отрицательные и положительные
	CHECK(result4 == std::vector<double>{ 0, 3, 5 });
}

TEST_CASE("PrintSortedNumbers()")
{
	std::streambuf* old_cout = std::cout.rdbuf();

	std::stringstream ss1;
	std::cout.rdbuf(ss1.rdbuf());
	PrintSortedNumbers(std::vector<double>{ -2, 1, 3 }); //вывод целых чисел и сортировка
	CHECK(ss1.str() == "-2.000 1.000 3.000\n");

	std::stringstream ss2;
	std::cout.rdbuf(ss2.rdbuf());
	PrintSortedNumbers(std::vector<double>{ -2.21, 1.11, 3.14 }); //вывод чисел с плавающей точкой без округления
	CHECK(ss2.str() == "-2.210 1.110 3.140\n");

	std::stringstream ss3;
	std::cout.rdbuf(ss3.rdbuf());
	PrintSortedNumbers(std::vector<double>{ 1.1125, -2.2146, 3.1450 }); //вывод чисел с плавающей точкой c округлением и сортировка
	CHECK(ss3.str() == "-2.215 1.113 3.145\n");

	std::cout.rdbuf(old_cout);
}