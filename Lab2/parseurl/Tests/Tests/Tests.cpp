#include "Tests/ParseUrl/ParseUrl.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <string>

TEST_CASE("ParseURL() - Invalid URL")
{
	Protocol protocol{};
	std::string host{};
	std::string document{};
	int port{};

	CHECK(!ParseURL("asdas", protocol, port, host, document)); //неверная строка

	CHECK(!ParseURL("abc://example.com:8080/index.html", protocol, port, host, document)); //неверный протокол

	CHECK(!ParseURL("://example.com:8080/index.html", protocol, port, host, document)); // нет протокола

	CHECK(!ParseURL("httpexample.com:8080/index.html", protocol, port, host, document)); // нет ://

	CHECK(!ParseURL("http://example.com:asd/index.html", protocol, port, host, document)); // в порте буквы

	CHECK(!ParseURL("http://example.com:0/index.html", protocol, port, host, document)); // порт < 1

	CHECK(!ParseURL("http://example.com:65536/index.html", protocol, port, host, document)); // порт > 65535
}

TEST_CASE("ParseURL() - Valid URL without port and docs")
{
	Protocol protocol{};
	std::string host{};
	std::string document{};
	int port{};

	//без порта и документов
	CHECK(ParseURL("http://example.com", protocol, port, host, document));
	CHECK(protocol == Protocol::HTTP);
	CHECK(port == 80);
	CHECK(host == "example.com");
	CHECK(document == "");
	
}

TEST_CASE("ParseURL() - Valid URL with port and docs")
{
	Protocol protocol{};
	std::string host{};
	std::string document{};
	int port{};

	//с портом и документом
	CHECK(ParseURL("htTp://example.com:8080/index.html", protocol, port, host, document));
	CHECK(protocol == Protocol::HTTP);
	CHECK(port == 8080);
	CHECK(host == "example.com");
	CHECK(document == "index.html");
}

TEST_CASE("ParseURL() - Valid URL big port")
{
	Protocol protocol{};
	std::string host{};
	std::string document{};
	int port{};

	//большой порт
	CHECK(ParseURL("http://www.mysite.com/docs/document1.html?page=30&lang=en#title", protocol, port, host, document));
	CHECK(protocol == Protocol::HTTP);
	CHECK(port == 80);
	CHECK(host == "www.mysite.com");
	CHECK(document == "docs/document1.html?page=30&lang=en#title");
}

TEST_CASE("ParseURL() - Valid URL with port and without docs")
{
	Protocol protocol{};
	std::string host{};
	std::string document{};
	int port{};

	//с портом и без доков
	CHECK(ParseURL("http://example.com:8080", protocol, port, host, document));
	CHECK(protocol == Protocol::HTTP);
	CHECK(port == 8080);
	CHECK(host == "example.com");
	CHECK(document == "");
}

TEST_CASE("ParseURL() - Valid URL without port and with docs")
{
	Protocol protocol{};
	std::string host{};
	std::string document{};
	int port{};

	//без портов и с докоами
	CHECK(ParseURL("http://example.com/docs", protocol, port, host, document));
	CHECK(protocol == Protocol::HTTP);
	CHECK(port == 80);
	CHECK(host == "example.com");
	CHECK(document == "docs");
}

TEST_CASE("ParseURL() - Valid URL https")
{
	Protocol protocol{};
	std::string host{};
	std::string document{};
	int port{};

	//https
	CHECK(ParseURL("https://example.com/docs", protocol, port, host, document));
	CHECK(protocol == Protocol::HTTPS);
	CHECK(port == 443);
	CHECK(host == "example.com");
	CHECK(document == "docs");
}

TEST_CASE("ParseURL() - Valid URL ftp")
{
	Protocol protocol{};
	std::string host{};
	std::string document{};
	int port{};

	//ftp
	CHECK(ParseURL("ftp://example.com/docs", protocol, port, host, document));
	CHECK(protocol == Protocol::FTP);
	CHECK(port == 21);
	CHECK(host == "example.com");
	CHECK(document == "docs");
}