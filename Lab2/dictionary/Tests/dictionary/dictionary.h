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

using Dictionary = std::map<std::string, std::string>;
using Pairs = std::vector<std::pair<std::string, std::string>>;

std::vector<std::string> ReadWordsFromString(const std::string& line);
Dictionary CreateDictionaryFromFile(std::ifstream& input);
void AddWordInDictionary(Dictionary& dictionary, const std::string& word, const std::string& translate);
bool FindWordInDictionary(const Dictionary& dictionary, const std::string& word, std::string& translatedWord);