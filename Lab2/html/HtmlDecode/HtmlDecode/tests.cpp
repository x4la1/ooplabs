#include "catch2/catch.hpp"
#include "HtmlDecode.h"
#include <string>

TEST_CASE("HtmlDecode()")
{
	std::string result1 = HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s"); //проверка всех сущностей
	CHECK(result1 == "Cat <says> \"Meow\". M&M's");

	std::string result2 = HtmlDecode("Cat &lt;says&gt; &quoot;Meow&quot;. M&amp;M&apos;s"); //несуществующая сущность
	CHECK(result2 == "Cat <says> &quoot;Meow\". M&M's");
}