#include "Shapes/Shapes/LineSegment.h"
#include "catch2/catch.hpp"
#include <iostream>

TEST_CASE("LineSegment() invalid points")
{
	CHECK_THROWS_AS(LineSegment(Point(2.5, 3.6), Point(2.5, 3.6), 0x121212), std::invalid_argument);
}

TEST_CASE("LineSegment() color < 0")
{
	CHECK_THROWS_AS(LineSegment(Point(2.5, 3.6), Point(2.5, 3.7), -10), std::invalid_argument);
}

TEST_CASE("LineSegment() color > 0xffffff")
{
	CHECK_THROWS_AS(LineSegment(Point(2.5, 3.6), Point(2.5, 3.7), 0xffffffff), std::invalid_argument);
}

TEST_CASE("GetArea()")
{
	LineSegment ls(Point(2.5, 3.6), Point(2.5, 3.7), 0x121212);
	CHECK(ls.GetArea() == 0);
}

TEST_CASE("GetPerimeter()")
{
	LineSegment ls(Point(1, 1), Point(1, 2), 0x121212);
	CHECK(ls.GetPerimeter() == 1);
}

TEST_CASE("GetStartPoint()")
{
	LineSegment ls(Point(1, 1), Point(1, 2), 0x121212);
	Point point = ls.GetStartPoint();
	CHECK(point.GetX() == 1);
	CHECK(point.GetY() == 1);
}

TEST_CASE("GetEndPoint()")
{
	LineSegment ls(Point(1, 1), Point(1, 2), 0x121212);
	Point point = ls.GetEndPoint();
	CHECK(point.GetX() == 1);
	CHECK(point.GetY() == 2);
}

