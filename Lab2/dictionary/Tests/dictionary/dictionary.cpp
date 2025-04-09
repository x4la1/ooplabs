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


std::string Trim(const std::string& str)
{
<<<<<<< HEAD
	size_t start = str.find_first_not_of(" \t\n\r");
=======
	size_t start = str.find_first_not_of(" \n\t\r");
>>>>>>> 149197f8e28b2a82d46b535aa49286d3a609d9d1
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