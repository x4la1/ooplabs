#include "Tests/dictionary/dictionary.h"
#include <catch2/catch.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <windows.h>

TEST_CASE("ReadWordsFromString()")
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	CHECK_THROWS_AS(ReadWordsFromString(" : abc, ads "), std::exception); //пустое слово
	CHECK_THROWS_AS(ReadWordsFromString("cat:  "), std::exception); // пустое слово
	CHECK_THROWS_AS(ReadWordsFromString("cat: asd: asd "), std::exception); // 2 двоеточия
	CHECK_THROWS_AS(ReadWordsFromString(""), std::exception); //пустая строка
	CHECK_THROWS_AS(ReadWordsFromString("cat:"), std::exception); //второго слова нет
	CHECK(ReadWordsFromString("cat: кот, кошка") == std::vector<std::string>{ "cat", "кот, кошка" }); //успешное выполнение
}

/* TEST_CASE("CreateDictionaryFromFile()")
{
<<<<<<< HEAD
=======
	Dictionary expectedResult1 = {
		{ "The Red Square", "Красная площадь" },
		{ "ball", "мяч" },
		{ "bye", "пока" },
		{ "cat", "кот, кошка" },
		{ "hello", "привет" },
		{ "meat", "мясо" }
	};
	Dictionary dict{};

	std::ifstream input1("input1.txt");
	dict = CreateDictionaryFromFile(input1);
	for (auto item: dict)
	{
		std::cout << item.first << " " << item.second << "\n";
	}

	CHECK(expectedResult1 == dict); // успешное считывание
}*/

TEST_CASE("CreateDictionaryFromFile() - empty string")
{
>>>>>>> 149197f8e28b2a82d46b535aa49286d3a609d9d1
	std::ifstream input2("input2.txt");
	CHECK_THROWS_AS(CreateDictionaryFromFile(input2), std::exception); //пустое слово
}

TEST_CASE("AddWordInDictionary()")
{
	Dictionary input1 = {
		{ "The Red Square", "Красная площадь" },
		{ "ball", "мяч" },
		{ "bye", "пока" },
		{ "cat", "кот, кошка" },
		{ "hello", "привет" },
	};
	Dictionary output1 = {
		{ "The Red Square", "Красная площадь" },
		{ "ball", "мяч" },
		{ "bye", "пока" },
		{ "cat", "кот, кошка" },
		{ "hello", "привет" },
		{ "meat", "мясо" }
	};
	AddWordInDictionary(input1, "meat", "мясо");
	CHECK(input1 == output1); //добавление слов
}

TEST_CASE("FindWordInDictionary() find word")
{
	Dictionary dict = {
		{ "The Red Square", "Красная площадь" },
		{ "ball", "мяч" },
		{ "bye", "пока" },
		{ "cat", "кот, кошка" },
		{ "hello", "привет" },
		{ "meat", "мясо" }
	};

	std::string word1 = "ball";
	std::string translatedWord{};
	FindWordInDictionary(dict, word1, translatedWord);
	CHECK(translatedWord == "мяч"); //поиск слова

	std::string word2 = "alo"; //несуществвующее слово
	CHECK(FindWordInDictionary(dict, word2, translatedWord) == false);
}