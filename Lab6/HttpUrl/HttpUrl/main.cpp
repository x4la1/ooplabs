#include <string>
#include <iostream>
#include "HttpUrl.h"

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		HttpUrl url(line);
		std::cout << "Protocol: " << ProtocolToString(url.GetProtocol()) << "\n"
				  << "Domain: " << url.GetDomain() << "\n"
			      << "Port: " << url.GetPort() << "\n"
			      << "Document: " << url.GetDocument() << "\n"
			      << "Url: " << url.GetURL() << "\n";
	}
	std::cout << "Hello World!\n";
}


