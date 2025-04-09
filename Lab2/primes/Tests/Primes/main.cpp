#include "Primes.h"
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
#include <chrono>

const uint32_t MAX_UPPER_BOUND = 100000000;
const uint32_t MIN_UPPER_BOUND = 0;

void PrintHelp() //help
{
	std::cout << "Usage: Primes.exe <upper bound> (0 - 100000000)\n";
}

void PrintSet(std::set<uint32_t> numbers)
{
	for (auto item : numbers)
	{
		std::cout << item << "\n";
	}
}

bool IsValidUpperBound(const std::string& upperBoundString) //вынес
{

	uint32_t upperBound{};
	try
	{
		upperBound = std::stoi(upperBoundString);
	}
	catch (std::invalid_argument& e)
	{
		return false;
	}
	catch (std::out_of_range& e)
	{
		return false;
	}

	if (upperBound > MAX_UPPER_BOUND || upperBound < MIN_UPPER_BOUND)
	{
		return false;
	}

	return true;
}


#ifndef UNIT_TEST

int main(int argc, char* argv[]) 
{
	if (argc != 2)
	{
		PrintHelp();
		return 1;
	}

	if (!IsValidUpperBound(std::string(argv[1])))
	{
		PrintHelp();
		return 1;
	}

	uint32_t upperBound = std::stoi(argv[1]); 

	auto start = std::chrono::high_resolution_clock::now();
	std::set<uint32_t> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	auto end = std::chrono::high_resolution_clock::now();
	auto duratation = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << duratation << "\n";

	//PrintSet(primeNumbers);

	return 0;
}

#endif