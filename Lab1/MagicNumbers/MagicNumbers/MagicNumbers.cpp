#include <iostream>
#include <cstdint>
#include <string>
using namespace std;


int main(int argc, char* argv[])
{
    
    if (argc == 2 || argc > 3) 
    {
        cout << "Usage: MagicNumbers.exe -find <number> OR MagicNumbers.exe\n";
        return 0;
    }
    else if (argc == 3) 
    {
        string param = argv[1];
        if (param != "-find") 
        {
            cout << "Usage: MagicNumbers.exe -find <number> OR MagicNumbers.exe\n";
            return 0;
        }
        else
        {
            cout << "There is no magic numbers in this range\n";
            return 0;
        }
    }

    uint64_t number = 0;
    if (cin >> number)
    {
        cout << "Non-magic\n";
    }
    else
    {
        cout << "Error\n";
    }

    return 0;
}

