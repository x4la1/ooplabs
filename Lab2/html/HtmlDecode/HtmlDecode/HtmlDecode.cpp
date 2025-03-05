#include "HtmlDecode.h"
#include <map>
#include <string>
#include <stdexcept>
#include <iostream>

const std::map<std::string, char> htmlSymbols{ { "&quot;", '"' }, { "&apos;", '\'' }, { "&lt;", '<' }, { "&gt;", '>' }, { "&amp;", '&' } };

std::string HtmlDecode(std::string const& html)
{
	std::string decodedString{};

	for (size_t i = 0; i < html.size(); ++i)
	{
		if (html[i] == '&')
		{
			size_t semicolonPosition = html.find(';', i);
			if (semicolonPosition != std::string::npos)
			{
				std::string htmlEntity = html.substr(i, semicolonPosition - i + 1); 
				auto symbol = htmlSymbols.find(htmlEntity);
				if (symbol != htmlSymbols.end())
				{
					decodedString += symbol->second;
					i = semicolonPosition;
					continue;
				}
			}
		}
		decodedString += html[i];
	}

	return decodedString;
}

#ifndef UNIT_TEST

int main()
{
	std::cout << HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
	return 0;
}

#endif
