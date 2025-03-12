#include <catch2/catch.hpp>
#include "HtmlDecode.h"
#include <string>
#include <stdexcept>


TEST_CASE("HtmlDecode()")
{
	std::string result1 = HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s"); //проверка всех сущностей
	CHECK(result1 == "Cat <says> \"Meow\". M&M's");
	
	std::string result2 = HtmlDecode("Cat <says> \"Meow\". MnMТs"); //без сущностей
	CHECK(result2 == "Cat <says> \"Meow\". MnMТs");

	CHECK_THROWS_AS(HtmlDecode("Cat &lt;says&gt; &quoot;Meow&quot;. M&amp;M&apos;s"), std::invalid_argument); //несуществующа€ сущность

	CHECK_THROWS_AS(HtmlDecode("Cat &lt;says&gt; &quoot;Meow&quot;. M&amp;M&aposs"), std::invalid_argument); //нет ; на конце
}

