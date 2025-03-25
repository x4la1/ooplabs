#include "Tests/ParseUrl/ParseUrl.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <string>

TEST_CASE("ParseURL() - Invalid URL")
{
	Url url{};

	CHECK(!ParseURL("asdas", url)); //неверная строка

	CHECK(!ParseURL("abc://example.com:8080/index.html", url)); //неверный протокол

	CHECK(!ParseURL("://example.com:8080/index.html", url)); // нет протокола

	CHECK(!ParseURL("httpexample.com:8080/index.html", url)); // нет ://

	CHECK(!ParseURL("http://example.com:asd/index.html", url)); // в порте буквы

	CHECK(!ParseURL("http://example.com:0/index.html", url)); // порт < 1

	CHECK(!ParseURL("http://example.com:65536/index.html", url)); // порт > 65535
}

TEST_CASE("ParseURL() - Valid URL without port and docs")
{
	Url url{};

	//без порта и документов
	CHECK(ParseURL("http://example.com", url));
	CHECK(url.protocol == Protocol::HTTP);
	CHECK(url.port == 80);
	CHECK(url.host == "example.com");
	CHECK(url.document == "");
}

TEST_CASE("ParseURL() - Valid URL with port and docs")
{
	Url url{};

	//с портом и документом
	CHECK(ParseURL("htTp://example.com:8080/index.html", url));
	CHECK(url.protocol == Protocol::HTTP);
	CHECK(url.port == 8080);
	CHECK(url.host == "example.com");
	CHECK(url.document == "index.html");
}

TEST_CASE("ParseURL() - Valid URL big port")
{
	Url url{};

	//большой порт
	CHECK(ParseURL("http://www.mysite.com/docs/document1.html?page=30&lang=en#title", url));
	CHECK(url.protocol == Protocol::HTTP);
	CHECK(url.port == 80);
	CHECK(url.host == "www.mysite.com");
	CHECK(url.document == "docs/document1.html?page=30&lang=en#title");
}

TEST_CASE("ParseURL() - Valid URL with port and without docs")
{
	Url url{};

	//с портом и без доков
	CHECK(ParseURL("http://example.com:8080", url));
	CHECK(url.protocol == Protocol::HTTP);
	CHECK(url.port == 8080);
	CHECK(url.host == "example.com");
	CHECK(url.document == "");
}

TEST_CASE("ParseURL() - Valid URL without port and with docs")
{
	Url url{};

	//без портов и с докоами
	CHECK(ParseURL("http://example.com/docs", url));
	CHECK(url.protocol == Protocol::HTTP);
	CHECK(url.port == 80);
	CHECK(url.host == "example.com");
	CHECK(url.document == "docs");
}

TEST_CASE("ParseURL() - Valid URL https")
{
	Url url{};

	//https
	CHECK(ParseURL("https://example.com/docs", url));
	CHECK(url.protocol == Protocol::HTTPS);
	CHECK(url.port == 443);
	CHECK(url.host == "example.com");
	CHECK(url.document == "docs");
}

TEST_CASE("ParseURL() - Valid URL ftp")
{
	Url url{};

	//ftp
	CHECK(ParseURL("ftp://example.com/docs", url));
	CHECK(url.protocol == Protocol::FTP);
	CHECK(url.port == 21);
	CHECK(url.host == "example.com");
	CHECK(url.document == "docs");
}