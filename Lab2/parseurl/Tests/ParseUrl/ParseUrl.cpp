#include "ParseUrl.h" 
#include <iostream>
#include <map>
#include <regex>
#include <stdexcept>
#include <string>

//map protol, struct, init protocol

const std::map<std::string, std::pair<Protocol, int>> PROTOCOLS{
	{ "http", { Protocol::HTTP, 80 } },
	{ "https", { Protocol::HTTPS, 443 } },
	{ "ftp", { Protocol::FTP, 21 } }
};
const int MAX_PORT_VALUE = 65535;
const int MIN_PORT_VALUE = 1;

void InitProtocol(const std::string& protocolString, Url& url)
{

	for (auto protocol : PROTOCOLS)
	{
		if (protocolString == protocol.first)
		{
			url.protocol = protocol.second.first;
			url.port = protocol.second.second;
		}
	}
}

bool InitPort(const std::string& portString, int& port)
{
	try
	{
		port = std::stoi(portString);
		if (port < MIN_PORT_VALUE || port > MAX_PORT_VALUE) //const вынес
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

bool ParseURL(const std::string& urlString, Url& url)
{
	std::regex urlPattern(R"(^(http|https|ftp)://([^/:]+)(:(\d+))?(/.*)?$)");
	std::smatch match{};

	std::string lowerCaseUrl = urlString;
	std::transform(lowerCaseUrl.begin(), lowerCaseUrl.end(), lowerCaseUrl.begin(), tolower);

	if (!std::regex_match(lowerCaseUrl, match, urlPattern))
	{
		return false;
	}

	std::string protocolString = match[1].str();
	InitProtocol(protocolString, url);

	url.host = match[2].str();

	if (match[3].matched)
	{
		if (!match[4].str().empty() && !InitPort(match[4].str(), url.port))
		{
			return false;
		}
	}

	if (match[5].matched)
	{
		url.document = match[5].str().substr(1);
	}
	else
	{
		url.document = "";
	}

	return true;
}