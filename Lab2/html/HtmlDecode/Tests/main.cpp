#include "HtmlDecode.h"
#include <iostream>
#include <string>

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
