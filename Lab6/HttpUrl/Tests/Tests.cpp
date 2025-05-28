#include "catch2/catch.hpp"
#include "HttpUrl/HttpUrl/HttpUrl.h"
#include <iostream>


TEST_CASE("HttpUrl(string) - ivalid string")
{
	CHECK_THROWS_AS(HttpUrl("asdasd"), CUrlParsingError);
	//HttpUrl url("htTp://example.com:80/index.html");
}

TEST_CASE("HttpUrl(string) - ivalid protocol")
{
	CHECK_THROWS_AS(HttpUrl("asd://example.com:80/index.html"), CUrlParsingError);
}

TEST_CASE("HttpUrl(string) - no protocol")
{
	CHECK_THROWS_AS(HttpUrl("://example.com:80/index.html"), CUrlParsingError);
}

TEST_CASE("HttpUrl(string) - no ://")
{
	CHECK_THROWS_AS(HttpUrl("httpexample.com:8080/index.html"), CUrlParsingError);
}

TEST_CASE("HttpUrl(string) - invalid port")
{
	CHECK_THROWS_AS(HttpUrl("http://example.com:asd/index.html"), CUrlParsingError);
}

TEST_CASE("HttpUrl(string) - port < 1")
{
	CHECK_THROWS_AS(HttpUrl("http://example.com:0/index.html"), CUrlParsingError);
}

TEST_CASE("HttpUrl(string) - port > 65535")
{
	CHECK_THROWS_AS(HttpUrl("http://example.com:65536/index.html"), CUrlParsingError);
}

TEST_CASE("HttpUrl(domain, document, protocol) - invalid domain")
{
	CHECK_THROWS_AS(HttpUrl("", "asd", Protocol::HTTP), std::invalid_argument);
}

TEST_CASE("HttpUrl(domain, document, protocol, port) - invalid port")
{
	CHECK_THROWS_AS(HttpUrl("example.com", "asd", Protocol::HTTP, 0), std::invalid_argument);
}

TEST_CASE("HttpUrl(url) - no port and document, default port")
{
	HttpUrl url("http://example.com");
	CHECK(url.GetDomain() == "example.com");
	CHECK(url.GetProtocol() == Protocol::HTTP);
	CHECK(url.GetPort() == 80);
	CHECK(url.GetDocument() == "/");
	CHECK(url.GetURL() == "http://example.com/");
}

TEST_CASE("HttpUrl(url) - with port and docs, default port")
{
	HttpUrl url("http://example.com:80/index.html");
	CHECK(url.GetDomain() == "example.com");
	CHECK(url.GetProtocol() == Protocol::HTTP);
	CHECK(url.GetPort() == 80);
	CHECK(url.GetDocument() == "/index.html");
	CHECK(url.GetURL() == "http://example.com/index.html");
}

TEST_CASE("HttpUrl(url) - with port and docs, not default port")
{
	HttpUrl url("http://example.com:18/index.html");
	CHECK(url.GetDomain() == "example.com");
	CHECK(url.GetProtocol() == Protocol::HTTP);
	CHECK(url.GetPort() == 18);
	CHECK(url.GetDocument() == "/index.html");
	CHECK(url.GetURL() == "http://example.com:18/index.html");
}

TEST_CASE("HttpUrl(url) - with port and without docs")
{
	HttpUrl url("http://example.com:1337");
	CHECK(url.GetDomain() == "example.com");
	CHECK(url.GetProtocol() == Protocol::HTTP);
	CHECK(url.GetPort() == 1337);
	CHECK(url.GetDocument() == "/");
	CHECK(url.GetURL() == "http://example.com:1337/");
}

TEST_CASE("HttpUrl(url) - without port and with docs, https")
{
	HttpUrl url("https://example.com/index.html");
	CHECK(url.GetDomain() == "example.com");
	CHECK(url.GetProtocol() == Protocol::HTTPS);
	CHECK(url.GetPort() == 443);
	CHECK(url.GetDocument() == "/index.html");
	CHECK(url.GetURL() == "https://example.com/index.html");
}

TEST_CASE("HttpUrl(url) - upper case protocol")
{
	HttpUrl url("hTtPS://example.com/index.html");
	CHECK(url.GetDomain() == "example.com");
	CHECK(url.GetProtocol() == Protocol::HTTPS);
	CHECK(url.GetPort() == 443);
	CHECK(url.GetDocument() == "/index.html");
	CHECK(url.GetURL() == "https://example.com/index.html");
}

TEST_CASE("HttpUrl(domain, document, protocol) - without protocol")
{
	HttpUrl url("example.com", "index.html");
	CHECK(url.GetDomain() == "example.com");
	CHECK(url.GetProtocol() == Protocol::HTTP);
	CHECK(url.GetPort() == 80);
	CHECK(url.GetDocument() == "/index.html");
	CHECK(url.GetURL() == "http://example.com/index.html");
}

TEST_CASE("HttpUrl(domain, document, protocol) - with protocol")
{
	HttpUrl url("example.com", "index.html", Protocol::HTTPS);
	CHECK(url.GetDomain() == "example.com");
	CHECK(url.GetProtocol() == Protocol::HTTPS);
	CHECK(url.GetPort() == 443);
	CHECK(url.GetDocument() == "/index.html");
	CHECK(url.GetURL() == "https://example.com/index.html");
}

TEST_CASE("HttpUrl(domain, document, protocol, port)")
{
	HttpUrl url("example.com", "index.html", Protocol::HTTPS, 552);
	CHECK(url.GetDomain() == "example.com");
	CHECK(url.GetProtocol() == Protocol::HTTPS);
	CHECK(url.GetPort() == 552);
	CHECK(url.GetDocument() == "/index.html");
	CHECK(url.GetURL() == "https://example.com:552/index.html");
}