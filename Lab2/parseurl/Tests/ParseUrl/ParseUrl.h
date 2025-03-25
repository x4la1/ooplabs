#include <string>

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

struct Url
{
	Protocol protocol;
	std::string host;
	int port;
	std::string document;
};

bool ParseURL(const std::string& urlString, Url& url);