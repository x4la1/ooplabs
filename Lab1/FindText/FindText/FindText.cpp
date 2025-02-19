#include <cstdint>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

struct Arguments
{
	std::string filename;
	std::string searchText;
};

std::optional<Arguments> ParseArguments(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: FindText.exe <file name> <text for search>\n";
		return std::nullopt;
	}

	std::string searchText(argv[2]);
	if (searchText == "")
	{
		std::cout << "Text for search must not be empty\n";
		return std::nullopt;
	}

	Arguments args{};
	args.filename = std::string{argv[1]};
	args.searchText = searchText;

	return args;
}

void FindText(std::ifstream& input, const std::string& searchText)
{
	std::vector<uint32_t> lineNumbers{};
	std::string line{};
	uint32_t lineCounter = 0;
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
		for (auto item : lineNumbers)
		{
			std::cout << item << "\n";
		}
	}
}

bool IsFileReadble(std::ifstream& input)
{
	if (input.peek() == EOF)
	{
		std::cout << "File can't be read\n";
		return false;
	}
	return true;
}

//ParseArguments возвращает объект
//пустой файл 
//права доступа

int main(int argc, char* argv[])
{
	auto args = ParseArguments(argc, argv);
	if (args == std::nullopt)
	{
		return 1;
	}

	std::ifstream input(args->filename);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << argv[1] << "'\n";
		return 1;
	}
	
	if (!IsFileReadble(input))
	{
		return 1;
	}
	
	FindText(input, args->searchText);

	return 0;
}
