#pragma once
#include <cstdint>
#include <ostream>

enum class Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

enum class WeekDay
{
	MONDAY = 1,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY,
};

class CDate
{
public:
	CDate();
	CDate(const uint32_t& day, const Month& month, const uint32_t& year);
	explicit CDate(const uint32_t& timestamp);	
	uint32_t GetTimestamp() const;
	uint32_t GetDay() const;
	Month GetMonth() const;
	uint32_t GetYear() const;
	WeekDay GetWeekDay() const;

	CDate& operator++();
	CDate operator++(int);
	CDate& operator--();
	CDate operator--(int);
	CDate operator+(const uint32_t& days) const;
	CDate operator-(const uint32_t& days) const;
	int32_t operator-(const CDate& other) const;
	CDate& operator+=(const uint32_t& days);
	CDate& operator-=(const uint32_t& days);
	auto operator<=>(const CDate&) const = default;

	//bool operator==(const CDate& other) const;
	//bool operator!=(const CDate& other) const;
	//bool operator<(const CDate& other) const;
	//bool operator>(const CDate& other) const;
	//bool operator<=(const CDate& other) const;
	//bool operator>=(const CDate& other) const;

private:
	uint32_t m_timestamp;
	static const uint32_t s_timestampStartYear;
	static const uint32_t s_maxTimestampDate;
	bool IsValidDate(const uint32_t& day, const Month& month, const uint32_t& year) const;
	uint32_t GetDaysInMonth(const Month& month, const uint32_t& year) const;
	uint32_t DateToTimestamp(const uint32_t& day, const uint32_t& month, const uint32_t& year) const;
	uint32_t TimestampToYear(const uint32_t& timestamp) const;
	uint32_t YearToTimestamp(const uint32_t& year) const;
	bool IsLeapYear(const uint32_t& year) const;
};

CDate operator+(const uint32_t& days, const CDate& date);
std::ostream& operator<<(std::ostream& os, const CDate& date);
std::istream& operator>>(std::istream& is, CDate& date);