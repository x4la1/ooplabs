#include "HtmlDecode.h"
#include <catch2/catch.hpp>
#include <stdexcept>
#include <string>

TEST_CASE("HtmlDecode() - проверка всех сущностей") //разные test cases + сущность в начале
{
	std::string result1 = HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s"); 
	CHECK(result1 == "Cat <says> \"Meow\". M&M's");
}

TEST_CASE("HtmlDecode() - без сущностей")
{
	std::string result2 = HtmlDecode("Cat <says> \"Meow\". MnMТs");
	CHECK(result2 == "Cat <says> \"Meow\". MnMТs");
}

TEST_CASE("HtmlDecode() - несуществующая сущность")
{
	CHECK_THROWS_AS(HtmlDecode("Cat &lt;says&gt; &quoot;Meow&quot;. M&amp;M&apos;s"), std::invalid_argument); 
}

TEST_CASE("HtmlDecode() - нет ; на конце")
{
	CHECK_THROWS_AS(HtmlDecode("Cat &lt;says&gt; &quoot;Meow&quot;. M&amp;M&aposs"), std::invalid_argument);
}

TEST_CASE("HtmlDecode() - сущность в начале")
{
	std::string result3 = HtmlDecode("&quot;Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
	CHECK("\"Cat <says> \"Meow\". M&M's");
}