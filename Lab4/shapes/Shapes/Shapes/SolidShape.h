#pragma once
#include "Shape.h";

class SolidShape : public Shape
{
public:
	uint32_t GetFillColor() const;

protected:
	double GetDistanceBetween(const Point& point1, const Point& point2) const;
	uint32_t m_fillColor;
};