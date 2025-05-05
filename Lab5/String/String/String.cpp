#include "String.h"
#include <iostream>
#include <stdexcept>
#include <cstring>

char* CMyString::s_empty = new char('\0');
CMyString::CMyString() :m_data{ s_empty }, m_length{ 0 }, m_capacity{ 0 } {}

CMyString::CMyString(const char* pString)
{
	if (!pString || strlen(pString) == 0)
	{
		m_data = s_empty;
		m_length = 0;
		m_capacity = 0;
		return;
	}
	m_length = strlen(pString);
	m_capacity = m_length;
	m_data = new char[m_length + 1];
	std::copy(pString, pString + m_length, m_data);
	m_data[m_length] = '\0';
}

CMyString::CMyString(const char* pString, size_t length)
{
	m_length = length;
	m_capacity = length;
	if (length == 0)
	{
		m_data = s_empty;
		return;
	}

	m_data = new char[length + 1];
	if (pString != nullptr)
	{
		std::copy(pString, pString + length, m_data);
	}
	m_data[length] = '\0';
}

CMyString::CMyString(CMyString const& other)
{
	if (other.m_data == s_empty)
	{
		m_data = s_empty;
		m_length = 0;
		m_capacity = 0;
		return;
	}
	m_length = other.m_length;
	m_capacity = other.m_capacity;
	m_data = new char[m_length + 1];
	std::copy(other.m_data, other.m_data + m_length + 1, m_data);
}

CMyString::CMyString(CMyString&& other) noexcept
{
	m_data = other.m_data;
	m_length = other.m_length;
	m_capacity = other.m_capacity;
	other.m_data = s_empty;
	other.m_length = 0;
	other.m_capacity = 0;
}

CMyString::CMyString(std::string const& stlString)
{
	m_length = stlString.length();
	m_capacity = m_length;
	if (m_length == 0)
	{
		m_data = s_empty;
		return;
	}
	m_data = new char[m_length + 1];
	std::copy(stlString.c_str(), stlString.c_str() + m_length, m_data);
	m_data[m_length] = '\0';
}

CMyString::~CMyString()
{
	if (m_data != s_empty)
	{
		delete[] m_data;
	}
}

size_t CMyString::GetLength()const
{
	return m_length;
}

size_t CMyString::GetCapacity() const
{
	return m_capacity;
}

const char* CMyString::GetStringData()const
{
	return m_data;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		throw std::out_of_range("Invalid string position\n");
	}
	length = std::min(length, m_length - start);
	return CMyString(m_data + start, length);
}

void CMyString::Clear()
{
	if (m_data != s_empty)
	{
		delete[] m_data;
	}
	m_data = s_empty;
	m_length = 0;
	m_capacity = 0;
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (this != &other)
	{
		if (m_data != s_empty)
		{
			delete[] m_data;
		}
		m_length = other.m_length;
		m_capacity = other.m_length;
		if (other.m_data == s_empty)
		{
			m_data = s_empty;
			return *this;
		}
		m_data = new char[m_length + 1];
		std::copy(other.m_data, other.m_data + m_length, m_data);
		m_data[m_length] = '\0';
	}
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (this != &other)
	{
		if (m_data != s_empty)
		{
			delete[] m_data;
		}
		m_data = other.m_data;
		m_length = other.m_length;
		m_capacity = other.m_capacity;
		other.m_data = s_empty;
		other.m_length = 0;
		other.m_capacity = 0;
	}
	return *this;
}

CMyString& CMyString::operator+=(const CMyString& other)
{
	if (other.m_data == s_empty)
	{
		return *this;
	}

	size_t newLength = m_length + other.m_length;
	if (newLength > m_capacity)
	{
		size_t newCapacity = std::max(m_capacity * 2, newLength);
		char* newData = new char[newCapacity + 1];
		std::copy(m_data, m_data + m_length, newData);
		if (m_data != s_empty)
		{
			delete[] m_data;
		}
		m_data = newData;
		m_capacity = newCapacity;
	}
	std::copy(other.m_data, other.m_data + other.m_length, m_data + m_length);
	m_length = newLength;
	m_data[m_length] = '\0';
}

CMyString CMyString::operator+(const CMyString& other) const
{
	if (other.m_data == s_empty)
	{
		return CMyString(*this);
	}

	size_t newLength = m_length + other.m_length;
	char* newData = new char[newLength + 1];
	std::copy(m_data, m_data + m_length, newData);
	std::copy(other.m_data, other.m_data + other.m_length, newData + m_length);
	newData[newLength] = '\0';
	return CMyString(newData, newLength);
}

CMyString CMyString::operator+(const std::string& stlString) const
{
	return *this + CMyString(stlString);
}

CMyString CMyString::operator+(const char* string) const
{
	return *this + CMyString(string);
}

bool CMyString::operator==(const CMyString& other) const
{
	if (m_length != other.m_length)
	{
		return false;
	}
	return std::equal(m_data, m_data + m_length, other.m_data);
}

bool CMyString::operator!=(const CMyString& other) const
{
	return !(*this == other);
}

bool CMyString::operator<(const CMyString& other) const
{
	return std::lexicographical_compare(m_data, m_data + m_length, other.m_data, other.m_data + other.m_length);
}

bool CMyString::operator>(const CMyString& other) const
{
	return other < *this;
}

bool CMyString::operator<=(const CMyString& other) const
{
	return !(*this > other);
}

bool CMyString::operator>=(const CMyString& other) const
{
	return !(*this < other);
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::out_of_range("Index out of range\n");
	}

	return m_data[index];
}

const char& CMyString::operator[](size_t index) const
{
	if (index >= m_length)
	{
		throw std::out_of_range("Index out of range\n");
	}

	return m_data[index];
}

std::ostream& operator<<(std::ostream& os, const CMyString& str)
{
	for (size_t i = 0; i < str.GetLength(); ++i)
	{
		os << str[i];
	}

	return os;
}

std::istream& operator>>(std::istream& is, CMyString& str) 
{
	std::string line;
	is >> line;
	CMyString temp(line);
	str = std::move(temp);
	return is;
}