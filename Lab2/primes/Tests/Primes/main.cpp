#include "Primes.h"
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
#include <chrono>

void PrintUsage() //help
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

	uint32_t upperBound{}; //valid вынести
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


	auto start = std::chrono::high_resolution_clock::now();
	std::set<uint32_t> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	auto end = std::chrono::high_resolution_clock::now();
	auto duratation = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << duratation << "\n";

	//PrintSet(primeNumbers);

	return 0;
}

#endif