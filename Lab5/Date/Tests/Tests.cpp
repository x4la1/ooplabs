#include "Date/Date/Date.h"
#include <catch2/catch.hpp>
#include <iostream>
#include <sstream>

TEST_CASE("Date(d,m,y) - invalid, 29 feb non leap year")
{
	CHECK_THROWS_AS(CDate(29, Month::FEBRUARY, 2023), std::invalid_argument);
}

TEST_CASE("Date(d,m,y) - invalid, 30 feb leap year")
{
	CHECK_THROWS_AS(CDate(30, Month::FEBRUARY, 2024), std::invalid_argument);
}

TEST_CASE("Date(d,m,y) - invalid, -1 jan")
{
	CHECK_THROWS_AS(CDate(-1, Month::JANUARY, 2024), std::invalid_argument);
}

TEST_CASE("Date(d,m,y) - invalid year > 9999")
{
	CHECK_THROWS_AS(CDate(1, Month::JANUARY, 10000), std::invalid_argument);
}

TEST_CASE("Date(d,m,y) - invalid year < 1970")
{
	CHECK_THROWS_AS(CDate(1, Month::JANUARY, 1969), std::invalid_argument);
}

TEST_CASE("Date(d,m,y) - invalid month > 12")
{
	CHECK_THROWS_AS(CDate(1, static_cast<Month>(13), 1970), std::invalid_argument);
}

TEST_CASE("Date(d,m,y) - invalid month < 1")
{
	CHECK_THROWS_AS(CDate(1, static_cast<Month>(0), 1970), std::invalid_argument);
}

TEST_CASE("Convert to timestamp 1 leap year")
{
	CDate date(1, static_cast<Month>(1), 1972);
	CHECK(date.GetTimestamp() == 730);
}

TEST_CASE("Convert to timestamp leap year")
{
	CDate date(31, static_cast<Month>(7), 1972);
	CHECK(date.GetTimestamp() == 942);
}

TEST_CASE("Convert to timestamp 1 leap year in range (1972)")
{
	CDate date(14, static_cast<Month>(3), 1973);
	CHECK(date.GetTimestamp() == 1168);
}

TEST_CASE("Convert to timestamp 2 leap year in range (1972, 1976)")
{
	CDate date(14, static_cast<Month>(3), 1977);
	CHECK(date.GetTimestamp() == 2629);
}

TEST_CASE("Convert to timestamp non leap year !/ 100 in range and leap year / 400")
{
	CDate date(14, static_cast<Month>(3), 2100);
	CHECK(date.GetTimestamp() == 47554);
}

TEST_CASE("Convet to timestamp 1970.01.01")
{
	CDate date(1, static_cast<Month>(1), 1970);
	CHECK(date.GetTimestamp() == 0);
}

TEST_CASE("CDate(timestamp) > 9999 year")
{
	CHECK_THROWS_AS(CDate(2932897), std::invalid_argument);
}

TEST_CASE("CDate(timestamp) - valid")
{
	CDate date(10000);
	CHECK(date.GetTimestamp() == 10000);
}

TEST_CASE("CDate()")
{
	CDate date;
	CHECK(date.GetTimestamp() == 0);
}

TEST_CASE("GetYear() 1")
{
	CDate date(1, static_cast<Month>(1), 1970);
	CHECK(date.GetYear() == 1970);
}

TEST_CASE("GetYear() 2")
{
	CDate date(14, static_cast<Month>(3), 2100);
	CHECK(date.GetYear() == 2100);
}

TEST_CASE("GetYear() 3")
{
	CDate date(1, static_cast<Month>(1), 9999);
	CHECK(date.GetYear() == 9999);
}

TEST_CASE("GetWeekday() 1")
{
	CDate date(1, static_cast<Month>(1), 1970);
	CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
}

TEST_CASE("GetWeekday() 2")
{
	CDate date(4, static_cast<Month>(5), 2025);
	CHECK(date.GetWeekDay() == WeekDay::SUNDAY);
}

TEST_CASE("GetWeekday() 4")
{
	CDate date(28, static_cast<Month>(4), 2025);
	CHECK(date.GetWeekDay() == WeekDay::MONDAY);
}

TEST_CASE("GetMonth() 1")
{
	CDate date(2, static_cast<Month>(5), 2025);
	CHECK(date.GetMonth() == Month::MAY);
}

TEST_CASE("GetMonth() 2")
{
	CDate date(1, static_cast<Month>(1), 1970);
	CHECK(date.GetMonth() == Month::JANUARY);
}

TEST_CASE("GetMonth() 3")
{
	CDate date(15, static_cast<Month>(12), 2005);
	CHECK(date.GetMonth() == Month::DECEMBER);
}

TEST_CASE("GetDay() 1")
{
	CDate date(1, static_cast<Month>(5), 1970);
	CHECK(date.GetDay() == 1);
}

TEST_CASE("GetDay() 29 feb")
{
	CDate date(29, static_cast<Month>(2), 2024);
	CHECK(date.GetDay() == 29);
}

TEST_CASE("GetDay() 28 feb")
{
	CDate date(28, static_cast<Month>(2), 2025);
	CHECK(date.GetDay() == 28);
}

TEST_CASE("GetDay() 31 day")
{
	CDate date(31, static_cast<Month>(12), 2025);
	CHECK(date.GetDay() == 31);
}

TEST_CASE("GetDay() 30 day")
{
	CDate date(30, static_cast<Month>(11), 2025);
	CHECK(date.GetDay() == 30);
}

TEST_CASE("++date invalid")
{
	CDate date(31, static_cast<Month>(12), 9999);
	CHECK_THROWS_AS(++date, std::invalid_argument);
}

TEST_CASE("++date valid with =")
{
	CDate date1(30, static_cast<Month>(12), 9999);
	CDate date2 = ++date1;
	CHECK(date1.GetTimestamp() == 2932896);
	CHECK(date2.GetTimestamp() == 2932896);
}

TEST_CASE("date++ invalid")
{
	CDate date(31, static_cast<Month>(12), 9999);
	CHECK_THROWS_AS(date++, std::invalid_argument);
}

TEST_CASE("date++ valid with =")
{
	CDate date1(30, static_cast<Month>(12), 9999);
	CDate date2 = date1++;
	CHECK(date1.GetTimestamp() == 2932896);
	CHECK(date2.GetTimestamp() == 2932895);
}

TEST_CASE("--date invalid")
{
	CDate date(1, static_cast<Month>(1), 1970);
	CHECK_THROWS_AS(--date, std::invalid_argument);
}

TEST_CASE("--date valid")
{
	CDate date1(2, static_cast<Month>(1), 1970);
	CDate date2 = --date1;
	CHECK(date1.GetTimestamp() == 0);
	CHECK(date2.GetTimestamp() == 0);
}

TEST_CASE("date-- invalid")
{
	CDate date(1, static_cast<Month>(1), 1970);
	CHECK_THROWS_AS(date--, std::invalid_argument);
}

TEST_CASE("date-- valid")
{
	CDate date1(2, static_cast<Month>(1), 1970);
	CDate date2 = date1--;
	CHECK(date1.GetTimestamp() == 0);
	CHECK(date2.GetTimestamp() == 1);
}

TEST_CASE("+days invalid")
{
	CDate date1(31, static_cast<Month>(12), 9999);
	CHECK_THROWS_AS(date1 + 1, std::invalid_argument);
}

TEST_CASE("date+days valid")
{
	CDate date1(1, static_cast<Month>(1), 1970);
	CHECK((date1 + 30).GetTimestamp() == 30);
}

TEST_CASE("days+date valid")
{
	CDate date1(1, static_cast<Month>(1), 1970);
	CHECK((30 + date1).GetTimestamp() == 30);
}

TEST_CASE("date-days invalid")
{
	CDate date1(1, static_cast<Month>(1), 1970);
	CHECK_THROWS_AS(date1 - 1, std::invalid_argument);
}

TEST_CASE("date-days valid")
{
	CDate date1(2, static_cast<Month>(1), 1970);
	CHECK((date1 - 1).GetTimestamp() == 0);
}

TEST_CASE("date-date positive")
{
	CDate date1(15, static_cast<Month>(1), 1970);
	CDate date2(1, static_cast<Month>(1), 1970);
	CHECK(date1 - date2 == 14);
}

TEST_CASE("date-date negative")
{
	CDate date1(15, static_cast<Month>(1), 1970);
	CDate date2(1, static_cast<Month>(1), 1970);
	CHECK(date2 - date1 == -14);
}

TEST_CASE("date-date zero")
{
	CDate date1(15, static_cast<Month>(1), 1970);
	CDate date2(15, static_cast<Month>(1), 1970);
	CHECK(date2 - date1 == 0);
}

TEST_CASE("+= days invalid")
{
	CDate date1(31, static_cast<Month>(12), 9999);
	CHECK_THROWS_AS(date1 += 1, std::invalid_argument);
}

TEST_CASE("+= days valid")
{
	CDate date1(1, static_cast<Month>(1), 1970);
	CHECK((date1 += 1).GetTimestamp() == 1);
}

TEST_CASE("-= days invalid")
{
	CDate date1(1, static_cast<Month>(1), 1970);
	CHECK_THROWS_AS(date1 -= 1, std::invalid_argument);
}

TEST_CASE("-= days valid")
{
	CDate date1(2, static_cast<Month>(1), 1970);
	CHECK((date1 -= 1).GetTimestamp() == 0);
}

TEST_CASE("== true")
{
	CDate date1(1, static_cast<Month>(1), 1970);
	CDate date2(1, static_cast<Month>(1), 1970);
	CHECK((date1 == date2) == true);
}

TEST_CASE("== false")
{
	CDate date1(2, static_cast<Month>(1), 1970);
	CDate date2(1, static_cast<Month>(1), 1970);
	CHECK((date1 == date2) == false);
}

TEST_CASE("!= true")
{
	CDate date1(2, static_cast<Month>(1), 1970);
	CDate date2(1, static_cast<Month>(1), 1970);
	CHECK((date1 != date2) == true);
}

TEST_CASE("!= false")
{
	CDate date1(1, static_cast<Month>(1), 1970);
	CDate date2(1, static_cast<Month>(1), 1970);
	CHECK((date1 != date2) == false);
}

TEST_CASE("> true")
{
	CDate date1(2, static_cast<Month>(1), 1970);
	CDate date2(1, static_cast<Month>(1), 1970);
	CHECK((date1 > date2) == true);
}

TEST_CASE("> false")
{
	CDate date1(1, static_cast<Month>(1), 1970);
	CDate date2(1, static_cast<Month>(1), 1970);
	CHECK((date1 > date2) == false);
}

TEST_CASE("< false")
{
	CDate date1(2, static_cast<Month>(1), 1970);
	CDate date2(1, static_cast<Month>(1), 1970);
	CHECK((date1 < date2) == false);
}

TEST_CASE("< true")
{
	CDate date1(1, static_cast<Month>(1), 1970);
	CDate date2(2, static_cast<Month>(1), 1970);
	CHECK((date1 < date2) == true);
}

TEST_CASE("<= true")
{
	CDate date1(2, static_cast<Month>(1), 1970);
	CDate date2(2, static_cast<Month>(1), 1970);
	CHECK((date1 <= date2) == true);
}

TEST_CASE(">= true")
{
	CDate date1(1, static_cast<Month>(1), 1970);
	CDate date2(1, static_cast<Month>(1), 1970);
	CHECK((date1 <= date2) == true);
}

TEST_CASE("<< month < 10 and day < 10")
{
	CDate date(1, static_cast<Month>(1), 1970);
	std::stringstream ss;
	ss << date;
	CHECK(ss.str() == "01.01.1970\n");
}

TEST_CASE("<< month > 10 and day > 10")
{
	CDate date(25, static_cast<Month>(12), 1970);
	std::stringstream ss;
	ss << date;
	CHECK(ss.str() == "25.12.1970\n");
}

TEST_CASE(">> invalid 1")
{
	CDate date;
	std::string line = "32.13.10000";
	std::stringstream ss(line);
	CHECK_THROWS_AS(ss >> date, std::invalid_argument);
}

TEST_CASE(">> invalid 2")
{
	CDate date;
	std::string line = "15/12/2005";
	std::stringstream ss(line);
	CHECK_THROWS_AS(ss >> date, std::invalid_argument);
}

TEST_CASE(">> invalid 3")
{
	CDate date;
	std::string line = "15a.12.2005";
	std::stringstream ss(line);
	CHECK_THROWS_AS(ss >> date, std::invalid_argument);
}