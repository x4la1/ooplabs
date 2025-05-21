#include "HttpUrl.h"
#include <sstream>

const unsigned short HttpUrl::s_maxPort = 65535;
const unsigned short HttpUrl::s_minPort = 1;
const std::regex HttpUrl::s_urlPattern(R"(^(http|https)://([^/:]+)(:(\d+))?(/.*)?$)", std::regex::icase);

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

HttpUrl::HttpUrl(const std::string& domain, const std::string& document, Protocol protocol)
{
	if (domain.empty())
	{
		throw std::invalid_argument("Domain must not be empty\n");
	}
	ProcessDomain(domain);
	ProcessDocument(document);
	m_protocol = protocol;
	SetDefaultPort();
}

HttpUrl::HttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port)
{
	if (domain.empty())
	{
		throw std::invalid_argument("Domain must not be empty\n");
	}
	if (!IsValidPort(port))
	{
		throw std::invalid_argument("Invalid must be in range 1 - 65535\n");
	}

	ProcessDomain(domain);
	ProcessDocument(document);
	m_protocol = protocol;
	m_port = port;
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
	m_protocol = it->second;
}

void HttpUrl::ProcessDomain(const std::string& domain)
{
	m_domain = domain;
}

void HttpUrl::ProcessPort(const std::string& port)
{
	uint32_t newPort;
	newPort = std::stoi(port);
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
	auto it = s_defaultPorts.find(m_protocol);
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