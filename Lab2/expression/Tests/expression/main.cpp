#include <iostream>
#include "expression.h"



#ifndef UNIT_TEST

int main()
{
	std::string line{};
	std::getline(std::cin, line);

	std::cout << CalculateExpression(line) << "\n";

	return 0;
}

#endif
