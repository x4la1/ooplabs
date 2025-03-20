#include "ParseUrl.h"
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

bool IsValidProtocol(std::string& protocolString, Protocol& protocol, int& port)
{
	std::transform(protocolString.begin(), protocolString.end(), protocolString.begin(), tolower);

	if (protocolString == "http") //map, struct, init protocol
	{
		protocol = Protocol::HTTP;
		port = 80;
	}
	else if (protocolString == "https")
	{
		protocol = Protocol::HTTPS;
		port = 443;
	}
	else if (protocolString == "ftp")
	{
		protocol = Protocol::FTP;
		port = 21;
	}
	else
	{
		return false;
	}

	return true;
}

bool IsValidPort(const std::string& portString, int& port)
{
	try
	{
		port = std::stoi(portString);
		if (port < 1 || port > 65535) //const вынести
		{
			return false;
		}
	}
	catch (std::invalid_argument& e)
	{
		return false;
	}
	catch (std::out_of_range& e)
	{
		return false;
	}

	return true;
}

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::regex urlPattern(R"(^(http|https|ftp)://([^/:]+)(:(\d+))?(/.*)?$)");
	std::smatch match{};

	std::string lowerCaseUrl = url;
	std::transform(lowerCaseUrl.begin(), lowerCaseUrl.end(), lowerCaseUrl.begin(), tolower); //lowercaseurl to all func

	if (!std::regex_match(lowerCaseUrl, match, urlPattern))
	{
		return false;
	}

	std::string protocolString = match[1].str();
	if (!IsValidProtocol(protocolString, protocol, port))
	{
		return false;
	}

	host = match[2].str();

	if (match[3].matched)
	{
		if (!match[4].str().empty() && !IsValidPort(match[4].str(), port))
		{
			return false;
		}
	}

	if (match[5].matched)
	{
		document = match[5].str().substr(1);
	}
	else
	{
		document = "";
	}

	return true;
}

#ifndef UNIT_TEST

int main()
{
	std::string url;
	std::getline(std::cin, url);

	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	if (ParseURL(url, protocol, port, host, document))
	{
		std::cout << url << "\n";
		std::cout << "HOST: " << host << "\n";
		std::cout << "PORT: " << port << "\n";
		std::cout << "DOC: " << document << "\n";
	}
	else
	{
		std::cout << "ERROR" << "\n";
	}

	return 0;
}

#endif
