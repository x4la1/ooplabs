#include "Shapes/Shapes/Rectangle.h"
#include "catch2/catch.hpp"

TEST_CASE("Rectangle() point1.x > point2.x")
{
	CHECK_THROWS_AS(Rectangle(Point(2, 3), Point(1, 2), 0x121212, 0x121212), std::invalid_argument);
}

TEST_CASE("Rectangle() point1.x == point2.x")
{
	CHECK_THROWS_AS(Rectangle(Point(1, 3), Point(1, 2), 0x121212, 0x121212), std::invalid_argument);
}

TEST_CASE("Rectangle() point1.y < point2.y")
{
	CHECK_THROWS_AS(Rectangle(Point(3, 1), Point(2, 2), 0x121212, 0x121212), std::invalid_argument);
}

TEST_CASE("Rectangle() point1.y == point2.y")
{
	CHECK_THROWS_AS(Rectangle(Point(3, 1), Point(2, 1), 0x121212, 0x121212), std::invalid_argument);
}

TEST_CASE("GetArea()")
{
	Rectangle rec(Point(2, 3), Point(5, 1), 0x121212, 0x121212);
	CHECK(rec.GetArea() == 6);
}

TEST_CASE("GetPerimeter()")
{
	Rectangle rec(Point(2, 3), Point(5, 1), 0x121212, 0x121212);
	CHECK(rec.GetPerimeter() == 10);
}

TEST_CASE("GetWidth()")
{
	Rectangle rec(Point(2, 3), Point(5, 1), 0x121212, 0x121212);
	CHECK(rec.GetWidth() == 3);
}


TEST_CASE("GetHeight()")
{
	Rectangle rec(Point(2, 3), Point(5, 1), 0x121212, 0x121212);
	CHECK(rec.GetHeight() == 2);
}