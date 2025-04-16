#pragma once
#include <string>
#include "ICanvasDrawable.h"

class Shape: public ICanvasDrawable
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	uint32_t GetOutlineColor() const;

protected:
	uint32_t m_outlineColor;
};
