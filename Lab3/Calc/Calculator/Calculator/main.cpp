#include <iostream>
#include <string>
#include "Controller.h"

int main()
{
	Controller calc;
	std::string line;
	while (std::getline(std::cin, line))
	{
		if (line == "end\n")
		{
			break;
		}
		try
		{
			calc.HandleCommand(line);
		}
		catch (std::exception& e)
		{
			std::cout << e.what();
		}
	}
}


