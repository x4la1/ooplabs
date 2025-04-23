#include <iostream>
#include <string>
#include "Calculator.h"

int main()
{
	Calculator calc;
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


