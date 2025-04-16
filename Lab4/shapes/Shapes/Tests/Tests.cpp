#include "Shapes/Shapes/Point.h"
#include <catch2/catch.hpp>

TEST_CASE("class Point x < 0")
{
	CHECK_THROWS_AS(Point(-1.1, 1.1), std::invalid_argument);
}

TEST_CASE("class Point y < 0")
{
	CHECK_THROWS_AS(Point(1.1, -1.1), std::invalid_argument);
}

TEST_CASE("class Point GetX()")
{
	Point point(12.5, 4.2);
	CHECK(point.GetX() == 12.5);
}

TEST_CASE("class Point GetY()")
{
	Point point(12.5, 4.2);
	CHECK(point.GetY() == 4.2);
}

