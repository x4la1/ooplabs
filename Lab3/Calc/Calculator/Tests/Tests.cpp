#include "catch2/catch.hpp"
#include <sstream>
#include <iostream>
#include "Calculator/Calculator/Controller.h"

TEST_CASE("Unknown command")
{
	Controller calc;
	CHECK_THROWS_AS(calc.HandleCommand("asd x"), std::invalid_argument);
}

TEST_CASE("Var - valid")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("var x");
	calc.HandleCommand("print x");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "x:nan\n");
}

TEST_CASE("Var - valid with diff symbols")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("var x123_asd2_111");
	calc.HandleCommand("print x123_asd2_111");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "x123_asd2_111:nan\n");
}

TEST_CASE("Var - invalid name")
{
	Controller calc;
	CHECK_THROWS_AS(calc.HandleCommand("var 1x"), std::invalid_argument);
}

TEST_CASE("let - invalid identifier")
{
	Controller calc;
	CHECK_THROWS_AS(calc.HandleCommand("let 1x = 1"), std::invalid_argument);
}

TEST_CASE("let - unknown variable")
{
	Controller calc;
	CHECK_THROWS_AS(calc.HandleCommand("let x = a"), std::invalid_argument);
}

TEST_CASE("let - identifier already exist")
{
	Controller calc;
	calc.HandleCommand("var x");
	CHECK_THROWS_AS(calc.HandleCommand("let x = a"), std::invalid_argument);
}

TEST_CASE("let - out of range")
{
	Controller calc;
	CHECK_THROWS_AS(calc.HandleCommand("let x = 999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"), std::out_of_range);
}

TEST_CASE("let - valid let = double, not exist")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("let x = 4.5");
	calc.HandleCommand("print x");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "x:4.500\n");
}

TEST_CASE("let - valid let = variable")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("let y = 13.37");
	calc.HandleCommand("let x = y");
	calc.HandleCommand("print x");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "x:13.370\n");
}

TEST_CASE("let - valid let = double, exist")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("var y");
	calc.HandleCommand("let y = 36.6");
	calc.HandleCommand("print y");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "y:36.600\n");
}

TEST_CASE("let - valid let = fn")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("let y = 5");
	calc.HandleCommand("fn dy = y*y");
	calc.HandleCommand("let x = dy");
	calc.HandleCommand("print x");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "x:25.000\n");
}

TEST_CASE("let - valid let = variable(nan)")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("var y");
	calc.HandleCommand("let x = y");
	calc.HandleCommand("print x");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "x:nan\n");
}

TEST_CASE("fn - invalid name")
{
	Controller calc;
	calc.HandleCommand("var x");
	CHECK_THROWS_AS(calc.HandleCommand("fn 1asd = x"), std::invalid_argument);
}

TEST_CASE("fn - identifier already exist")
{
	Controller calc;
	calc.HandleCommand("var x");
	CHECK_THROWS_AS(calc.HandleCommand("fn x = x"), std::invalid_argument);
}

TEST_CASE("fn -  operand not exist")
{
	Controller calc;
	CHECK_THROWS_AS(calc.HandleCommand("fn x = y"), std::invalid_argument);
}

TEST_CASE("fn - second operand not exist")
{
	Controller calc;
	calc.HandleCommand("var x");
	CHECK_THROWS_AS(calc.HandleCommand("fn a = x + y"), std::invalid_argument);
}

TEST_CASE("fn - invalid operation")
{
	Controller calc;
	calc.HandleCommand("var x");
	calc.HandleCommand("var y");
	CHECK_THROWS_AS(calc.HandleCommand("fn a = x ^ y"), std::invalid_argument);
}

TEST_CASE("fn - valid + ")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("let x = 5.2");
	calc.HandleCommand("let y = 4.8");
	calc.HandleCommand("fn XPlusY = x+ y");
	calc.HandleCommand("print XPlusY");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "XPlusY:10.000\n");
}

TEST_CASE("fn - valid - ")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("let x = 5.2");
	calc.HandleCommand("let y = 4.8");
	calc.HandleCommand("fn XPlusY = x- y");
	calc.HandleCommand("print XPlusY");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "XPlusY:0.400\n");
}

TEST_CASE("fn - valid * ")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("let x = 3.5");
	calc.HandleCommand("let y = 2");
	calc.HandleCommand("fn XPlusY =x* y");
	calc.HandleCommand("print XPlusY");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "XPlusY:7.000\n");
}

TEST_CASE("fn - valid / ")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("let x = 7");
	calc.HandleCommand("let y = 2");
	calc.HandleCommand("fn XPlusY =x/ y");
	calc.HandleCommand("print XPlusY");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "XPlusY:3.500\n");
}

TEST_CASE("fn - valid divided by 0 ")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("let x = 7");
	calc.HandleCommand("let y = 0");
	calc.HandleCommand("fn XPlusY =x/ y");
	calc.HandleCommand("print XPlusY");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "XPlusY:nan\n");
}

TEST_CASE("fn - valid + nan")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("var x");
	calc.HandleCommand("let y = 5");
	calc.HandleCommand("fn XPlusY =x+ y");
	calc.HandleCommand("print XPlusY");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "XPlusY:nan\n");
}

TEST_CASE("fn - valid - nan")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("var x");
	calc.HandleCommand("let y = 5");
	calc.HandleCommand("fn XPlusY =x- y");
	calc.HandleCommand("print XPlusY");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "XPlusY:nan\n");
}

TEST_CASE("fn - valid * nan")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("var x");
	calc.HandleCommand("let y = 5");
	calc.HandleCommand("fn XPlusY =x* y");
	calc.HandleCommand("print XPlusY");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "XPlusY:nan\n");
}

TEST_CASE("fn - valid / nan")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("var x");
	calc.HandleCommand("let y = 5");
	calc.HandleCommand("fn XPlusY =x/ y");
	calc.HandleCommand("print XPlusY");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "XPlusY:nan\n");
}

TEST_CASE("fn - valid 1 operand is function")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("let x = 5");
	calc.HandleCommand("let y = 5");
	calc.HandleCommand("let z = 2");
	calc.HandleCommand("fn XPlusY =x+ y");
	calc.HandleCommand("fn XpYdZ = XPlusY * z");
	calc.HandleCommand("print XpYdZ");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "XpYdZ:20.000\n");
}

TEST_CASE("fn - valid 2 operand is function")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("let x = 5");
	calc.HandleCommand("let y = 5");
	calc.HandleCommand("let z = 2");
	calc.HandleCommand("fn XPlusY =x+ y");
	calc.HandleCommand("fn XpYdZ = XPlusY * z");
	calc.HandleCommand("fn xd = XPlusY / XpYdZ");
	calc.HandleCommand("print xd");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "xd:0.500\n");
}

TEST_CASE("printvars")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("let x = -5");
	calc.HandleCommand("let y = x");
	calc.HandleCommand("var z");
	calc.HandleCommand("printvars");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "x:-5.000\ny:-5.000\nz:nan\n");
}

TEST_CASE("printfns + alphabet")
{
	std::streambuf* oldCout = std::cout.rdbuf();
	std::stringstream ss;
	std::cout.rdbuf(ss.rdbuf());

	Controller calc;
	calc.HandleCommand("let x = 5");
	calc.HandleCommand("let y = 5");
	calc.HandleCommand("let z = 2");
	calc.HandleCommand("var d");
	calc.HandleCommand("fn XPlusY =x+ y");
	calc.HandleCommand("fn XpYdZ = XPlusY * z");
	calc.HandleCommand("fn xd = XPlusY / XpYdZ");
	calc.HandleCommand("fn nan = xd + d");
	calc.HandleCommand("printfns");

	std::string out = ss.str();
	std::cout.rdbuf(oldCout);
	CHECK(out == "XPlusY:10.000\nXpYdZ:20.000\nnan:nan\nxd:0.500\n");
}