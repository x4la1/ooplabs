#include "vector.h"
#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>

const std::set<char> validDigits{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '-' };

bool IsValidChar(const char& ch)
{
	if (!validDigits.count(ch))
	{
		return false;
	}
	return true;
}

bool IsStringContainInvalidSymbols(const std::string& token)
{
	return token.find("-.") != std::string::npos
		|| token.find(".-") != std::string::npos
		|| token.find("--") != std::string::npos
		|| token.find("..") != std::string::npos;
}

bool IsValidNumber(const std::string& token)
{
	if (token.empty())
	{
		return false;
	}

	if (token[0] == '.' || (token[0] == '0' && token.size() > 1) || !IsValidChar(token[0]))
	{
		return false;
	}

	if (IsStringContainInvalidSymbols(token))
	{
		return false;
	}

	bool isDot = false;
	for (size_t i = 1; i < token.length(); ++i)
	{
		if (!IsValidChar(token[i]))
		{
			return false;
		}

		if (token[i] == '.')
		{
			if (isDot)
			{
				return false;
			}
			isDot = true;
		}
		if (token[i] == '-')
		{
			return false;
		}
	}

	return true;
}

bool IsNumber(const std::string& token)
{
	if (!IsValidNumber(token))
	{
		return false;
	}

	try
	{
		std::stod(token);
	}
	catch (std::out_of_range& )
	{
		return false;
	}
	catch (std::invalid_argument& )
	{
		return false;
	}

	return true;
}

std::vector<double> ReadNumbers()
{
	std::string token{};
	std::vector<double> numbers{};
	std::string line{};

	std::getline(std::cin, line);
	std::stringstream ss(line);

	while (ss >> token)
	{
		if (IsNumber(token))
		{
			numbers.push_back(std::stod(token));
		}
		else
		{
			throw std::invalid_argument("Invalid argument");
		}
	}

	return numbers;
}

double FindMeanOfPositiveNumbers(const std::vector<double>& numbers)
{
	uint32_t positiveNumberCounter{};
	double sum{};
	for (auto num : numbers)
	{
		if (num > 0)
		{
			positiveNumberCounter++;
			sum += num;
		}
	}

	if (positiveNumberCounter == 0)
	{
		return 0;
	}

	return sum / positiveNumberCounter;
}

std::vector<double> ProcessNumbers(const std::vector<double>& numbers)
{
	std::vector<double> newNumbers{};
	double mean = FindMeanOfPositiveNumbers(numbers);
	if (mean == 0)
	{
		return numbers;
	}

	for (auto num : numbers)
	{
		newNumbers.push_back(num + mean);
	}
	return newNumbers;
}

void PrintSortedNumbers(std::vector<double> numbers)
{
	std::sort(numbers.begin(), numbers.end());

	for (size_t i = 0; i < numbers.size(); ++i)
	{
		std::cout << std::fixed << std ::setprecision(3) << numbers[i];
		if (i == numbers.size() - 1)
		{
			std::cout << "\n";
		}
		else
		{
			std::cout << " ";
		}
	}
}

#ifndef UNIT_TESTS

int main()
{
	std::vector<double> numbers{};
	try
	{
		numbers = ReadNumbers();
	}
	catch (std::invalid_argument)
	{
		std::cout << "ERROR\n";
		return 0;
	}

	if (numbers.empty())
	{
		return 0;
	}

	std::vector<double> newNumbers = ProcessNumbers(numbers);
	PrintSortedNumbers(newNumbers);

	return 0;
}

#endif