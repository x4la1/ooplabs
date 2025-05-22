#pragma once
#include <stdexcept>
#include <cstdint>
#include <string>
#include "UrlParsingError.h"
#include <map>
#include <regex>

enum class Protocol
{
	HTTP,
	HTTPS
};

class HttpUrl
{
public:
	HttpUrl(const std::string& url);
	HttpUrl(const std::string& domain, const std::string& document, Protocol protocol = Protocol::HTTP);
	HttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

	static const std::map<std::string, Protocol> s_protocols;

private:
	void ProcessProtocol(const std::string& protocol);
	void ProcessDomain(const std::string& domain);
	void ProcessPort(const std::string& port);
	void ProcessDocument(const std::string& document);
	void SetDefaultPort();
	bool IsDefaultPort() const;
	bool IsValidPort(const uint32_t& port) const;
	void ParseAndInitUrl(const std::string& url); //suda

	static const std::regex s_urlPattern;
	static const std::map<Protocol, unsigned short> s_defaultPorts;
	static const unsigned short s_maxPort;
	static const unsigned short s_minPort;

	Protocol m_protocol = Protocol::HTTP;
	std::string m_domain;
	unsigned short m_port = 0;
	std::string m_document;
};


std::string ProtocolToString(const Protocol& protocol);