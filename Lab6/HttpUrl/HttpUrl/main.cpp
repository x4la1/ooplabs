#include <string>
#include <iostream>
#include "HttpUrl.h"

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		try
		{
			HttpUrl url(line);
			std::cout << "Protocol: " << ProtocolToString(url.GetProtocol()) << "\n"
				<< "Domain: " << url.GetDomain() << "\n"
				<< "Port: " << url.GetPort() << "\n"
				<< "Document: " << url.GetDocument() << "\n"
				<< "Url: " << url.GetURL() << "\n";
		}
		catch(std::exception& e)
		{
			std::cout << e.what();
		}
	}
}


