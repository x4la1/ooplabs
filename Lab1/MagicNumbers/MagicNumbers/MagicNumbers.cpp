#include <iostream>
#include <cstdint>
#include <string>

bool IsValidParams(int argc, char* argv[])
{
    if (argc == 2 || argc > 3)
    {
        std::cout << "Usage: MagicNumbers.exe -find <number> OR MagicNumbers.exe\n";
        return false;
    }
    else if (argc == 3)
    {
        std::string firstParameter = argv[1];
        if (firstParameter != "-find")
        {
            std::cout << "Usage: MagicNumbers.exe -find <number> OR MagicNumbers.exe\n";
            return false;
        }
        else
        {
            std::cout << "There is no magic numbers in this range\n"; //вынести
            return false;
        }
    }

    return true;
}

//вынести isMagicNumbers

int main(int argc, char* argv[])
{
    if (!IsValidParams(argc, argv)) return 0;

    uint64_t number = 0;
    if (std::cin >> number)
    {
        std::cout << "Non-magic\n";
    }
    else
    {
        std::cout << "Error\n";
    }

    return 0;
}

