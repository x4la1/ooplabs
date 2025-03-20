#include "HtmlDecode.h"
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

const std::map<std::string, char> HTML_SYMBOLS{ { "&quot;", '"' }, { "&apos;", '\'' }, { "&lt;", '<' }, { "&gt;", '>' }, { "&amp;", '&' } };

std::string HtmlDecode(std::string const& html)
{
	std::string decodedString{};

	for (size_t i = 0; i < html.size(); ++i)
	{
		if (html[i] == '&')
		{
			size_t semicolonPosition = html.find(';', i);

			if (semicolonPosition == std::string::npos)
			{
				throw std::invalid_argument("Invalid HTML symbol\n");
			}

			std::string htmlEntity = html.substr(i, semicolonPosition - i + 1);
			auto symbol = HTML_SYMBOLS.find(htmlEntity);

			if (symbol != HTML_SYMBOLS.end())
			{
				decodedString += symbol->second;
				i = semicolonPosition;
				continue;
			}
			else
			{
				throw std::invalid_argument("Invalid HTML symbol\n");
			}
		}
		decodedString += html[i];
	}

	return decodedString;
}
