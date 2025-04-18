#pragma once
#include <string>
//to string getfillcolor getoutcolor вынести
class IShape //virtual distrcut у всех интерфесов дублирование 
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;
};
