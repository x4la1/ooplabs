#include "Shapes/Shapes/Triangle.h"
#include "catch2/catch.hpp"

TEST_CASE("Triangle() invalid triangle 1")
{
	CHECK_THROWS_AS(Triangle(Point(1, 1), Point(3, 1), Point(2, 1), 0x000010, 0x11ff2f), std::invalid_argument);
}

TEST_CASE("Triangle() outline color < 0")
{
	CHECK_THROWS_AS(Triangle(Point(1, 1), Point(3, 1), Point(2, 2), -10, 0x11ff2f), std::invalid_argument);
}

TEST_CASE("Triangle() outline color > 0xffffff")
{
	CHECK_THROWS_AS(Triangle(Point(1, 1), Point(3, 1), Point(2, 2), 0x121212, 0xfffffffff), std::invalid_argument);
}

TEST_CASE("Triangle() fill color < 0")
{
	CHECK_THROWS_AS(Triangle(Point(1, 1), Point(3, 1), Point(2, 2), 0x11ff2f, -10), std::invalid_argument);
}

TEST_CASE("Triangle() fill color > 0xffffff")
{
	CHECK_THROWS_AS(Triangle(Point(1, 1), Point(3, 1), Point(2, 2), 0xfffffffff, 0x121212), std::invalid_argument);
}

TEST_CASE("GetArea()")
{
	Triangle triangle(Point(1, 1), Point(3, 1), Point(2, 2), 0x121212, 0x121212);
	CHECK(triangle.GetArea() == 1);
}

TEST_CASE("GetPerimeter()")
{
	Triangle triangle(Point(1, 1), Point(3, 1), Point(2, 2), 0x121212, 0x121212);
	CHECK(triangle.GetPerimeter() == (2 + std::sqrt(2)*2 ));
}

TEST_CASE("GetVertex1()")
{
	Triangle triangle(Point(1, 1), Point(3, 1), Point(2, 2), 0x121212, 0x121212);
	Point point = triangle.GetVertex1();
	CHECK(point.GetX() == 1.0);
	CHECK(point.GetY() == 1.0);
}

TEST_CASE("GetVertex2()")
{
	Triangle triangle(Point(1, 1), Point(3, 1), Point(2, 2), 0x121212, 0x121212);
	Point point = triangle.GetVertex2();
	CHECK(point.GetX() == 3.0);
	CHECK(point.GetY() == 1.0);
}

TEST_CASE("GetVertex3()")
{
	Triangle triangle(Point(1, 1), Point(3, 1), Point(2, 2), 0x121212, 0x121212);
	Point point = triangle.GetVertex3();
	CHECK(point.GetX() == 2.0);
	CHECK(point.GetY() == 2.0);
}


