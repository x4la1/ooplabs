#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <windows.h>
#include "dictionary.h"

using Dictionary = std::map<std::string, std::string>;
using Pairs = std::vector<std::pair<std::string, std::string>>;

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

void PrintUsing()
{
	std::cout << "Using: dictionary.exe [filename]\n";
}

void SetupConsoleCP()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

std::string Trim(const std::string& str)
{
	size_t start = str.find_first_not_of(" \t\n\r");
	if (start == std::string::npos)
	{
		return "";
	}

	return str.substr(start);
}

std::vector<std::string> ReadWordsFromString(const std::string& line)
{
	std::vector<std::string> wordsList{};
	std::string word{};
	std::stringstream ss(line);

	while (std::getline(ss, word, ':'))
	{
		word = Trim(word);
		if (word.empty())
		{
			throw std::exception("Words must not be empty\n");
		}
		wordsList.push_back(word);
	}

	if (wordsList.size() != 2)
	{
		throw std::exception("Invalid string");
	}
	return wordsList;
}

void AddPairsInDictionary(Dictionary& dictionary, const Pairs& pairs)
{
	for (auto item : pairs)
	{
		dictionary.insert(item);
	}
}

Dictionary CreateDictionaryFromFile(std::ifstream& input)
{
	std::string line{};
	Dictionary dictionary{};
	std::vector<std::string> words{};
	while (std::getline(input, line))
	{
		if (line.empty())
		{
			continue;
		}
		words = ReadWordsFromString(line);
		dictionary.insert(std::make_pair(words[0], words[1]));
	}

	return dictionary;
}

void AddWordInDictionary(Dictionary& dictionary, const std::string& word, const std::string& translate)
{
	dictionary.insert(make_pair(word, translate));
}

void SaveDictionary(const Dictionary& dictionary, const std::string& filename)
{
	std::ofstream output(filename);
	for (auto item: dictionary)
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

bool FindWordInDictionary(const Dictionary& dictionary, const std::string& word, std::string& translatedWord)
{
	auto foundedWord = dictionary.find(word);
	if (foundedWord == dictionary.end())
	{
		return false;
	}
	translatedWord = foundedWord->second;

	return true;
}

#ifndef UNIT_TEST

int main(int argv, char* argc[])
{
	SetupConsoleCP();
	auto filename = ParseArguments(argv, argc);
	if (filename == std::nullopt)
	{
		PrintUsing();
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

	if (!filename.has_value())
	{
		filename = "dictionary.txt";
	}

	std::string word{};
	std::string translatedWord{};
	std::string line{};
	std::string letter{};
	size_t pairsCount = dictionary.size();
	while (true)
	{
		std::getline(std::cin, word);
		if (word == "...")
		{
			ExitProgram(pairsCount, dictionary, filename.value());
			return 0;
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
				ExitProgram(pairsCount, dictionary, filename.value());
				return 0;
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

#endif
