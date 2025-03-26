#include <catch2/catch.hpp>
#include "Tests/expression/expression.h"

TEST_CASE("Calculate expression() оператор + и 1 аргумент")
{
	CHECK(CalculateExpression("(+ 7)") == 7);
}

TEST_CASE("Calculate expression() оператор * и 1 аргумент")
{
	CHECK(CalculateExpression("(* 8)") == 8);
}

TEST_CASE("Calculate expression() оператор + и 2 аргумента")
{
	CHECK(CalculateExpression("(+ 2 3)") == 5);
}

TEST_CASE("Calculate expression() оператор + и > 2 аргументов")
{
	CHECK(CalculateExpression("(+ 2 3 4)") == 9);
}

TEST_CASE("Calculate expression() оператор * и 2 аргумента")
{
	CHECK(CalculateExpression("(* 2 3)") == 6);
}

TEST_CASE("Calculate expression() оператор * и > 2 аргумента")
{
	CHECK(CalculateExpression("(* 2 3 4)") == 24);
}

TEST_CASE("Calculate expression() оператор + с отрицательным аргументом")
{
	CHECK(CalculateExpression("(+ -2 3)") == 1);
}

TEST_CASE("Calculate expression() оператор * с отрицательным аргументом")
{
	CHECK(CalculateExpression("(* -2 3)") == -6);
}

TEST_CASE("Calculate expression() вложенность + *")
{
	CHECK(CalculateExpression("(+ (* 2 3) (* 3 4))") == 18);
}

TEST_CASE("Calculate expression() вложенность * +")
{
	CHECK(CalculateExpression("(* (+ 1 2) (+ 3 1))") == 12);
}

TEST_CASE("Calculate expression() большая вложенность ")
{
	CHECK(CalculateExpression("(+ 5 (* 2 3 2) (+ 5 (+ 2 5) (* 2 2) ))") == 33);
}