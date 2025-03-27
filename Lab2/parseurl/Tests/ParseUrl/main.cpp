#include "ParseUrl.h"
#include <iostream>
#include <map>
#include <regex>
#include <stdexcept>
#include <string>


#ifndef UNIT_TEST

int main()
{
	std::string urlString;
	std::getline(std::cin, urlString);

	Url url{};
	if (ParseURL(urlString, url))
	{
		std::cout << urlString << "\n";
		std::cout << "HOST: " << url.host << "\n";
		std::cout << "PORT: " << url.port << "\n";
		std::cout << "DOC: " << url.document << "\n";
	}
	else
	{
		std::cout << "ERROR\n";
	}

	return 0;
}

#endif
