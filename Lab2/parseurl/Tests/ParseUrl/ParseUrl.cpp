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
		if (port < MIN_PORT_VALUE || port > MAX_PORT_VALUE) //const �����
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

void ParseProtocol(const std::smatch& match, Url& url)
{
	InitProtocol(match[1].str(), url);
}

void ParseDocument(const std::smatch& match, Url& url)
{
	if (match[5].matched)
	{
		url.document = match[5].str().substr(1);
	}
	else
	{
		url.document = "";
	}
}

void ParseHost(const std::smatch& match, Url& url)
{
	url.host = match[2].str();
}

bool ParsePort(std::smatch& match, Url& url)
{
	if (match[3].matched)
	{
		if (!match[4].str().empty() && !InitPort(match[4].str(), url.port))
		{
			return false;
		}
	}

	return true;
}

bool ParseURL(const std::string& urlString, Url& url) //raspil на parse protocol и тд
{
	std::regex urlPattern(R"(^(http|https|ftp)://([^/:]+)(:(\d+))?(/.*)?$)");
	std::smatch match{};

	std::string lowerCaseUrl = urlString;
	std::transform(lowerCaseUrl.begin(), lowerCaseUrl.end(), lowerCaseUrl.begin(), tolower);

	if (!std::regex_match(lowerCaseUrl, match, urlPattern))
	{
		return false;
	}

	ParseProtocol(match, url);
	ParseHost(match, url);
	if (!ParsePort(match, url))
	{
		return false;
	}
	ParseDocument(match, url);
	
	return true;
}


for()
{
	