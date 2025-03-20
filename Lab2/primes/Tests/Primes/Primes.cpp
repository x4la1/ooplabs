#include "Primes.h"
#include <chrono>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

std::set<uint32_t> GeneratePrimeNumbersSet(const uint32_t& upperBound)
{
	std::vector<bool> primeIndexes(upperBound + 1, true);

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