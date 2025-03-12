#include "Primes.h"
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
#include <chrono>

std::set<uint32_t> GeneratePrimeNumbersSet(uint32_t upperBound)
{
	std::vector<bool> primeIndexes(upperBound + 1, true);
	primeIndexes[0] = false;
	primeIndexes[1] = false;

	for (uint32_t i = 2; i * i <= upperBound; ++i)
	{
		if (primeIndexes[i] == true)
		{
			for (uint32_t j = i * i; j < upperBound; j += i)
			{
				primeIndexes[j] = false;
			}
		}
	}

	std::set<uint32_t> primeNumbers{};
	for (uint32_t i = 2; i < upperBound; ++i)
	{
		if (primeIndexes[i])
		{
			primeNumbers.insert(i);
		}
	}

	return primeNumbers;
}

void PrintUsage()
{
	std::cout << "Usage: Primes.exe <upper bound>\n";
}

void PrintSet(std::set<uint32_t> numbers)
{
	for (auto item : numbers)
	{
		std::cout << item << "\n";
	}
}

#ifndef UNIT_TEST

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		PrintUsage();
		return 1;
	}

	uint32_t upperBound{};
	try
	{
		upperBound = std::stoi(argv[1]);
	}
	catch (std::invalid_argument& e)
	{
		PrintUsage();
		return 1;
	}
	catch (std::out_of_range& e)
	{
		std::cout << "Upper bound exceeds the max value\n";
		return 1;
	}

	if (upperBound > 100000000 || upperBound < 0)
	{
		std::cout << "Upper bound must be in range 0-100000000\n";
		return 1;
	}


	//auto start = std::chrono::high_resolution_clock::now();
	std::set<uint32_t> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	//auto end = std::chrono::high_resolution_clock::now();
	//auto duratation = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	//std::cout << duratation << "\n";

	PrintSet(primeNumbers);

	return 0;
}

#endif