#include "Tests/Primes/Primes.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <set>

TEST_CASE("GeneratePrimeNumbersSet() - не пустое множество")
{
	CHECK(GeneratePrimeNumbersSet(10) == std::set<uint32_t>{ 2, 3, 5, 7 });
}

TEST_CASE("GeneratePrimeNumbersSet() - пустое множество")
{
	CHECK(GeneratePrimeNumbersSet(1) == std::set<uint32_t>{});
}

TEST_CASE("GeneratePrimeNumbersSet() - максимальное значение")
{
	CHECK(GeneratePrimeNumbersSet(100000000).size() == 5761455);
}