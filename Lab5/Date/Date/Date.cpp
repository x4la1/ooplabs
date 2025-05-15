#include "Date.h"
#include <iostream>
#include <regex>
#include <stdexcept>

const uint32_t CDate::s_maxTimestampDate = 2932896;
const uint32_t CDate::s_timestampStartYear = 1970;

CDate::CDate(const uint32_t& day, const Month& month, const uint32_t& year)
{
	if (!IsValidDate(day, month, year))
	{
		throw std::invalid_argument("Invalid date\n");
	}

	m_timestamp = DateToTimestamp(day, static_cast<uint32_t>(month), year);
}

CDate::CDate(const uint32_t& timestamp)
{
	if (timestamp > s_maxTimestampDate)
	{
		throw std::invalid_argument("Invalid timestamp\n");
	}

	m_timestamp = timestamp;
}

CDate::CDate()
{
	m_timestamp = 0;
}

uint32_t CDate::GetDay() const
{
	uint32_t year = GetYear();
	uint32_t daysLeft = m_timestamp - YearToTimestamp(year);
	uint32_t daysInMonth;
	for (uint32_t i = 1; i <= 12; ++i)
	{
		daysInMonth = GetDaysInMonth(static_cast<Month>(i), year);
		if (daysLeft < daysInMonth)
		{
			return daysLeft + 1;
		}
		daysLeft -= daysInMonth;
	}
}

Month CDate::GetMonth() const
{
	uint32_t year = GetYear();
	uint32_t daysLeft = m_timestamp - YearToTimestamp(year);
	uint32_t daysInMonth;
	for (uint32_t i = 1; i <= 12; ++i)
	{
		daysInMonth = GetDaysInMonth(static_cast<Month>(i), year);
		if (daysLeft < daysInMonth)
		{
			return static_cast<Month>(i);
		}
		daysLeft -= daysInMonth;
	}
}

uint32_t CDate::GetYear() const
{
	return TimestampToYear(m_timestamp);
}

WeekDay CDate::GetWeekDay() const
{
	uint32_t weekday = (m_timestamp + 4) % 7;
	if (weekday == 0)
	{
		weekday = 7;
	}

	return static_cast<WeekDay>(weekday);
}

bool CDate::IsValidDate(const uint32_t& day, const Month& month, const uint32_t& year) const
{
	if (year < 1970 || year > 9999) //const
	{
		return false;
	}

	if (month < Month::JANUARY || month > Month::DECEMBER)
	{
		return false;
	}

	if (day < 1 || day > GetDaysInMonth(month, year))
	{
		return false;
	}

	return true;
}

uint32_t CDate::GetDaysInMonth(const Month& month, const uint32_t& year) const
{
	switch (month)
	{
	case Month::FEBRUARY:
		return IsLeapYear(year) ? 29 : 28;
	case Month::APRIL:
		return 30;
	case Month::JUNE:
		return 30;
	case Month::SEPTEMBER:
		return 30;
	case Month::NOVEMBER:
		return 30;
	default:
		return 31;
	}
}

uint32_t CDate::DateToTimestamp(const uint32_t& day, const uint32_t& month, const uint32_t& year) const
{
	uint32_t days = YearToTimestamp(year);

	for (uint32_t i = 1; i < month; ++i)
	{
		days += GetDaysInMonth(static_cast<Month>(i), year);
	}
	days += (day - 1);
	return days;
}

bool CDate::IsLeapYear(const uint32_t& year) const
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

uint32_t CDate::TimestampToYear(const uint32_t& timestamp) const
{
	uint32_t years = timestamp / 365; //const
	uint32_t testYear = s_timestampStartYear + years;
	uint32_t days = YearToTimestamp(testYear);

	while (days > timestamp)
	{
		years--;
		testYear--;
		days = YearToTimestamp(testYear);
	}

	return 1970 + years; //const
}

uint32_t CDate::YearToTimestamp(const uint32_t& year) const
{
	uint32_t days = (year - s_timestampStartYear) * 365;
	uint32_t prevYear = year - 1;
	days += (prevYear / 4 - s_timestampStartYear / 4) - (prevYear / 100 - s_timestampStartYear / 100) + (prevYear / 400 - s_timestampStartYear / 400);

	return days;
}

uint32_t CDate::GetTimestamp() const
{
	return m_timestamp;
}

CDate& CDate::operator++()
{
	if (m_timestamp == s_maxTimestampDate)
	{
		throw std::invalid_argument("Date must be in range 01.01.1070 - 31.12.9999\n");
	}
	m_timestamp++;
	return *this;
}

CDate CDate::operator++(int)
{
	CDate prevDate(*this);
	++(*this);
	return prevDate;
}

CDate& CDate::operator--()
{
	if (m_timestamp == 0)
	{
		throw std::invalid_argument("Date must be in range 01.01.1070 - 31.12.9999\n");
	}
	m_timestamp--;
	return *this;
}

CDate CDate::operator--(int)
{
	CDate prevDate(*this);
	--(*this);
	return prevDate;
}

CDate CDate::operator+(const uint32_t& days) const
{
	if (m_timestamp + days > s_maxTimestampDate)
	{
		throw std::invalid_argument("Date must be in range 01.01.1070 - 31.12.9999\n");
	}
	uint32_t newTimestamp = m_timestamp + days;

	return CDate(newTimestamp);
}

CDate operator+(const uint32_t& days, const CDate& date)
{
	return date + days;
}

CDate CDate::operator-(const uint32_t& days) const
{
	if (m_timestamp - days < 0)
	{
		throw std::invalid_argument("Date must be in range 01.01.1070 - 31.12.9999\n");
	}
	uint32_t newTimestamp = m_timestamp - days;

	return CDate(newTimestamp);
}

int32_t CDate::operator-(const CDate& other) const
{
	return static_cast<int32_t>(m_timestamp) - static_cast<int32_t>(other.m_timestamp);
}

CDate& CDate::operator+=(const uint32_t& days)
{
	if (m_timestamp + days > s_maxTimestampDate)
	{
		throw std::invalid_argument("Date must be in range 01.01.1070 - 31.12.9999\n");
	}
	m_timestamp += days;
	return *this;
}

CDate& CDate::operator-=(const uint32_t& days)
{
	if (static_cast<int32_t>(m_timestamp) - static_cast<int32_t>(days) < 0)
	{
		throw std::invalid_argument("Date must be in range 01.01.1070 - 31.12.9999\n");
	}
	m_timestamp -= days;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const CDate& date)
{
	if (date.GetDay() < 10)
	{
		os << '0';
	}
	os << date.GetDay() << ".";

	if (static_cast<uint32_t>(date.GetMonth()) < 10)
	{
		os << '0';
	}
	os << static_cast<uint32_t>(date.GetMonth()) << "." << date.GetYear() << "\n";
	return os;
}

std::istream& operator>>(std::istream& is, CDate& date)
{
	std::string line;
	std::getline(is, line);

	std::regex dateRegex("^([0-2][0-9]|3[0-1])\\.(0[1-9]|1[0-2])\\.(19[7-9][0-9]\\d{2}|[2-9]\\d{3})$"); //const 2-9 0-9 0-9 0-9
	std::smatch match;

	if (!std::regex_match(line, match, dateRegex))
	{
		throw std::invalid_argument("Date must be dd.mm.yyyy\n");
	}
	date = CDate(std::stoi(match[1]), static_cast<Month>(std::stoi(match[2])), std::stoi(match[3]));
	return is;
}

/* bool CDate::operator==(const CDate& other) const
{
	return m_timestamp == other.m_timestamp;
}

bool CDate::operator!=(const CDate& other) const
{
	return m_timestamp != other.m_timestamp;
}

bool CDate::operator<(const CDate& other) const
{
	return m_timestamp < other.m_timestamp;
}

bool CDate::operator>(const CDate& other) const
{
	return m_timestamp > other.m_timestamp;
}

bool CDate::operator<=(const CDate& other) const
{
	return m_timestamp <= other.m_timestamp;
}

bool CDate::operator>=(const CDate& other) const
{
	return m_timestamp >= other.m_timestamp;
}*/