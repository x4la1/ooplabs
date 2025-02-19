#include <cstdint>
#include <iostream>
#include <optional>
#include <string>
#include <cstdint>

bool IsValidArguments(int argc, char* argv[])
{
	if (argc == 2 || argc > 3)
	{
		std::cout << "Usage: MagicNumbers.exe -find <number> OR MagicNumbers.exe\n";
		return false;
	}

	if (argc == 3)
	{
		std::string firstParameter = argv[1];
		if (firstParameter != "-find")
		{
			std::cout << "Usage: MagicNumbers.exe -find <number> OR MagicNumbers.exe\n";
			return false;
		}
	}
	return true;
}

//вынести isMagicNumber
//-find logica
int main(int argc, char* argv[])
{
	if (argc != 1)
	{
		if (IsValidArguments(argc, argv))
		{
			std::cout << "There is no magic numbers in this range\n";
			return 0;
		}
		else
		{
			return 1;
		}
	}

	uint64_t number = 0;
	if (std::cin >> number)
	{
		std::cout << "Non-magic\n";
	}
	else
	{
		std::cout << "Error\n";
		return 1;
	}

	return 0;
}
