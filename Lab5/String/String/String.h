#pragma once
#include <string>

class CMyString
{
public:
    CMyString();
    CMyString(const char* pString);
    CMyString(const char* pString, size_t length);
    CMyString(std::string const& stlString);

    CMyString(CMyString const& other);
    CMyString(CMyString&& other) noexcept;
    ~CMyString();
    
    size_t GetLength()const;
    size_t GetCapacity() const;
    const char* GetStringData()const;
    CMyString SubString(size_t start, size_t length)const;
    void Clear();

    CMyString& operator=(const CMyString& other);
    CMyString& operator=(CMyString&& other) noexcept;

    CMyString& operator+=(const CMyString& other);
    CMyString operator+(const CMyString& other) const;
    CMyString operator+(const std::string& stlString) const;
    CMyString operator+(const char* string) const;

    bool operator==(const CMyString& other) const;
    bool operator!=(const CMyString& other) const;
    bool operator<(const CMyString& other) const;
    bool operator>(const CMyString& other) const;
    bool operator<=(const CMyString& other) const;
    bool operator>=(const CMyString& other) const;

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    static char* s_empty;
private:
	char* m_data = s_empty;
	size_t m_length = 0;
	size_t m_capacity = 0;
};
std::ostream& operator<<(std::ostream& os, const CMyString& str);
std::istream& operator>>(std::istream& is, CMyString& str);

