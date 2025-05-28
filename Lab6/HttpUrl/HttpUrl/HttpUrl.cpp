#include "HttpUrl.h"
#include <sstream>

const unsigned short HttpUrl::s_maxPort = 65535;
const unsigned short HttpUrl::s_minPort = 1;
const std::regex HttpUrl::s_urlPattern(R"(^(http|https)://([^/:]+)(:([1-9]\d+))?(/.*)?$)", std::regex::icase);

const std::map<std::string, Protocol> HttpUrl::s_protocols =
{
	{ "http", Protocol::HTTP },
	{ "https", Protocol::HTTPS },
};

const std::map<Protocol, unsigned short> HttpUrl::s_defaultPorts =
{
	{  Protocol::HTTP, 80  },
	{  Protocol::HTTPS, 443  },
};

HttpUrl::HttpUrl(const std::string& url)
{
	ParseAndInitUrl(url);
}

HttpUrl::HttpUrl(const std::string& domain, const std::string& document, Protocol protocol)
{
	try
	{
		ParseAndInitUrl(ProtocolToString(protocol) + "://" + domain + "/" + document);
	}
	catch (CUrlParsingError& e)
	{
		throw std::invalid_argument(e.what());
	}
}

HttpUrl::HttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port)
{
	try
	{
		ParseAndInitUrl(ProtocolToString(protocol) + "://" + domain + ":" + std::to_string(port) + "/" + document);
	}
	catch (CUrlParsingError& e)
	{
		throw std::invalid_argument(e.what());
	}
}

std::string HttpUrl::GetURL() const
{
	std::stringstream url{};
	url << ProtocolToString(m_protocol) << "://" << GetDomain();
	if (!IsDefaultPort())
	{
		url << ":" << GetPort();
	}
	url << GetDocument();
	return url.str();
}

Protocol HttpUrl::GetProtocol() const
{
	return m_protocol;
}

std::string HttpUrl::GetDomain() const
{
	return m_domain;
}

std::string HttpUrl::GetDocument() const
{
	return m_document;
}

unsigned short HttpUrl::GetPort() const
{
	return m_port;
}

void HttpUrl::ProcessProtocol(const std::string& protocol)
{
	std::string lowerProtocol = protocol;
	std::transform(lowerProtocol.begin(), lowerProtocol.end(), lowerProtocol.begin(), ::tolower);

	auto it = s_protocols.find(lowerProtocol);
	if (it == s_protocols.end())
	{
		throw std::invalid_argument("Invalid protocol\n");
	}
	m_protocol = it->second; //не нашел
}

void HttpUrl::ProcessDomain(const std::string& domain) //domain to lower;
{
	std::string lowerDomain = domain;
	std::transform(lowerDomain.begin(), lowerDomain.end(), lowerDomain.begin(), ::tolower);
	m_domain = lowerDomain;
}

void HttpUrl::ProcessPort(const std::string& port)
{
	uint32_t newPort;
	try
	{
		newPort = std::stoi(port); //try catch;
	}
	catch (std::out_of_range& e)
	{
		throw std::invalid_argument("Port must be in range 1 - 65535\n");
	}

	if (!IsValidPort(newPort))
	{
		throw std::invalid_argument("Port must be in range 1 - 65535\n");
	}

	m_port = static_cast<unsigned short>(newPort);
}

void HttpUrl::ProcessDocument(const std::string& document)
{
	if (document.empty())
	{
		m_document = "/";
		return;
	}

	if (document[0] != '/')
	{
		m_document = '/' + document;
		return;
	}

	m_document = document;
}

void HttpUrl::SetDefaultPort()
{
	auto it = s_defaultPorts.find(m_protocol);//не нашел
	if (it == s_defaultPorts.end())
	{
		throw std::invalid_argument("Invalid protocol\n");
	}
	m_port = it->second;
}

bool HttpUrl::IsDefaultPort() const
{
	auto it = s_defaultPorts.find(m_protocol);
	if (it->second == m_port)
	{
		return true;
	}

	return false;
}

bool HttpUrl::IsValidPort(const uint32_t& port) const
{
	return port >= s_minPort && port <= s_maxPort;
}

std::string ProtocolToString(const Protocol& protocol)
{
	for (auto item : HttpUrl::s_protocols)
	{
		if (item.second == protocol)
		{
			return item.first;
		}
	}
}

void HttpUrl::ParseAndInitUrl(const std::string& url)
{
	std::smatch match{};
	if (!std::regex_match(url, match, s_urlPattern))
	{
		throw CUrlParsingError("Invalid url\n");
	}

	ProcessProtocol(match[1]);
	ProcessDomain(match[2]);
	try
	{
		match[3].matched ? ProcessPort(match[4]) : SetDefaultPort();
	}
	catch (std::invalid_argument& e)
	{
		throw CUrlParsingError(e.what());
	}

	ProcessDocument(match[5]);
}