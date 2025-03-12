#include "HtmlDecode.h"
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

const std::map<std::string, char> htmlSymbols{ { "&quot;", '"' }, { "&apos;", '\'' }, { "&lt;", '<' }, { "&gt;", '>' }, { "&amp;", '&' } };

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
			auto symbol = htmlSymbols.find(htmlEntity);

			if (symbol != htmlSymbols.end())
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

#ifndef UNIT_TEST

int main()
{
	std::string line{};
	std::string decodedLine{};

	while (std::getline(std::cin, line))
	{
		if (line == "end")
		{
			break;
		}
		try
		{
			decodedLine = HtmlDecode(line);
		}
		catch (std::invalid_argument& e)
		{
			std::cout << e.what();
			continue;
		}
		std::cout << decodedLine << "\n";
	}

	return 0;
}

#endif
