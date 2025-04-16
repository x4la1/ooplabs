#include "Shapes/Shapes/Circle.h"
#include "catch2/catch.hpp"
#include <numbers>

TEST_CASE("Circle() radius == 0")
{
	CHECK_THROWS_AS(Circle(Point(1, 1), 0, 0x121212, 0x121212), std::invalid_argument);
}

TEST_CASE("Circle() radius < 0")
{
	CHECK_THROWS_AS(Circle(Point(1, 1), -2, 0x121212, 0x121212), std::invalid_argument);
}

TEST_CASE("Circle() circle out of positive axes")
{
	CHECK_THROWS_AS(Circle(Point(1, 1), 4, 0x121212, 0x121212), std::invalid_argument);
}

TEST_CASE("GetArea()")
{
	Circle circ(Point(3,3), 2, 0x121212, 0x121212);
	CHECK(circ.GetArea() == std::numbers::pi*4);
}

TEST_CASE("GetPerimeter()")
{
	Circle circ(Point(3, 3), 2, 0x121212, 0x121212);
	CHECK(circ.GetPerimeter() == std::numbers::pi * 4);
}
