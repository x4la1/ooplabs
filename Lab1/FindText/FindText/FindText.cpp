#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool IsValidParameters(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: FindText.exe <file name> <text for search>\n";
        return false;
    }

    std::string searchText = argv[2];
    if (searchText == "")
    {
        std::cout << "Text for search must not be empty\n";
        return false;
    }

    return true;
}

void FindText(std::ifstream &input, std::string searchText)
{
    std::vector<int> lineNumbers;
    std::string line;
    int lineCounter = 0; //name
    while (getline(input, line))
    {
        lineCounter++;
        if (line.find(searchText) != std::string::npos)
        {
            lineNumbers.push_back(lineCounter);
        }
    }

    if (lineNumbers.empty())
    {
        std::cout << "Text not found\n";
    }
    else
    {
        for (int item : lineNumbers)
        {
            std::cout << item << "\n";
        }
    }
}

int main(int argc, char* argv[])
{
    //функция возвращает структуру аргументов
    //проверка пустой строки в findText
    //права доступа
    if (!IsValidParameters(argc, argv)) return 1;

    std::ifstream input;
    input.open(argv[1]);
    if (!input.is_open())
    {
        std::cout << "Failed to open '" << argv[1] << "'\n";
        return 0;
    }
    
    FindText(input, argv[2]);

    return 0;
}
