#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage: FindText.exe <file name> <text for search>\n";
        return 0;
    }

    ifstream input;
    input.open(argv[1]);
    if (!input.is_open())
    {
        cout << "Failed to open '" << argv[1] << "'\n";
        return 0;
    }

    string searchText = argv[2];
    if (searchText == "")
    {
        cout << "Text for search must not be empty\n";
        return 0;
    }


    vector<int> lineNumbers = {};
    std::string line;
    int lineNumber = 0;
    while (getline(input, line))
    {
        lineNumber++;
        if (line.find(searchText) != string::npos)
        {
            lineNumbers.push_back(lineNumber);
        }
    }

    if (lineNumbers.empty())
    {
        cout << "Text not found\n";
    }
    else
    {
        for (int item : lineNumbers)
        {
            cout << item << "\n";
        }
    }


    return 0;
}
