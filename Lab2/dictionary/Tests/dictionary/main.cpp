#include "dictionary.h"
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <windows.h>

using Dictionary = std::map<std::string, std::string>;
using Pairs = std::vector<std::pair<std::string, std::string>>;

void PrintHelp()
{
	std::cout << "Using: dictionary.exe [filename]\n";
}

std::optional<std::string> ParseArguments(int& argv, char* argc[])
{
	std::string filename{};

	if (argv > 2)
	{
		return std::nullopt;
	}

	if (argv == 2)
	{
		filename = argc[1];
	}

	return filename;
}

void SaveDictionary(const Dictionary& dictionary, const std::string& filename)
{
	std::ofstream output(filename);
	for (auto item : dictionary)
	{
		output << item.first << ": " << item.second << "\n";
	}
}

void ExitProgram(const size_t& pairsCount, const Dictionary& dictionary, const std::string& filename)
{
	std::string letter{};

	if (pairsCount != dictionary.size())
	{
		std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
	}

	std::getline(std::cin, letter);
	if (letter == "Y" || letter == "y")
	{
		SaveDictionary(dictionary, filename);
		std::cout << "Изменения сохранены. До свидания.";
	}
}

void SetupConsoleCP()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
}

void RunProgram(Dictionary& dictionary, const std::string filename)
{
	std::string word{};
	std::string translatedWord{};
	std::string line{};
	std::string letter{};
	size_t pairsCount = dictionary.size();
	SetupConsoleCP();
	while (true)
	{
		std::getline(std::cin, word);
		if (word == "...")
		{
			ExitProgram(pairsCount, dictionary, filename);
			break;
		}

		if (word.empty())
		{
			continue;
		}

		if (FindWordInDictionary(dictionary, word, translatedWord))
		{
			std::cout << translatedWord << "\n";
		}
		else
		{
			std::cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа.\n";
			std::getline(std::cin, line);
			if (line == "...")
			{
				ExitProgram(pairsCount, dictionary, filename);
				break;
			}
			if (line.empty())
			{
				std::cout << "Слово \"" << word << "\"проигнорировано.\n";
				continue;
			}
			else
			{
				AddWordInDictionary(dictionary, word, line);
			}
		}
	}
}

#ifndef UNIT_TEST

int main(int argv, char* argc[])
{
	auto filename = ParseArguments(argv, argc);
	if (filename == std::nullopt)
	{
		PrintHelp();
		return 1;
	}

	Dictionary dictionary{};
	if (!filename.value().empty())
	{
		std::ifstream input(filename.value());
		if (!input.is_open())
		{
			std::cout << "Can't open file\n";
			return 1;
		}

		try
		{
			dictionary = CreateDictionaryFromFile(input);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << "\n";
			return 1;
		}
	}
	else
	{
		filename = "dictionary.txt";
	}

	for (auto item : dictionary)
	{
		std::cout << item.first << " " << item.second << "\n";
	}

	RunProgram(dictionary, filename.value());

	return 0;
}

#endif