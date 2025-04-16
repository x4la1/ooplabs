#include "SolidShape.h"
#include <cmath>

uint32_t SolidShape::GetFillColor() const
{
	return m_fillColor;
}

double SolidShape::GetDistanceBetween(const Point& point1, const Point& point2) const
{
	return std::sqrt(std::pow((point2.GetX() - point1.GetX()), 2) + std::pow((point2.GetY() - point1.GetY()), 2));
}