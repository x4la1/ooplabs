#include <iostream>
#include <catch2/catch.hpp>
#include "Tests/dictionary/dictionary.h"
#include <stdexcept>
#include <fstream>

TEST_CASE("ReadWordsFromString()")
{
	CHECK_THROWS_AS(ReadWordsFromString(" : abc, ads "), std::exception); //пустое слово
	CHECK_THROWS_AS(ReadWordsFromString("cat:  "), std::exception); // пустое слово
	CHECK_THROWS_AS(ReadWordsFromString("cat: asd: asd "), std::exception); // 2 двоеточия
	CHECK_THROWS_AS(ReadWordsFromString(""), std::exception); //пустая строка
	CHECK_THROWS_AS(ReadWordsFromString("cat:"), std::exception); //второго слова нет
	CHECK(ReadWordsFromString("cat: кот, кошка") == std::vector<std::string>{ "cat", "кот, кошка" }); //успешное выполнение
}

TEST_CASE("CreateDictionaryFromFile()")
{
	Dictionary expectedResult1 = { { "The Red Square", "Красная площадь" },
		{ "ball", "мяч" },
		{ "bye", "пока" },
		{ "cat", "кот, кошка" },
		{ "hello", "привет" },
		{ "meat", "мясо" } };
	std::ifstream input1("input1.txt");
	CHECK(expectedResult1 == CreateDictionaryFromFile(input1)); // успешное считывание
	
	std::ifstream input2("input2.txt");
	CHECK_THROWS_AS(CreateDictionaryFromFile(input2), std::exception); //пустое слово
}

TEST_CASE("AddWordInDictionary()")
{
	Dictionary input1 = { { "The Red Square", "Красная площадь" },
		{ "ball", "мяч" },
		{ "bye", "пока" },
		{ "cat", "кот, кошка" },
		{ "hello", "привет" },};
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