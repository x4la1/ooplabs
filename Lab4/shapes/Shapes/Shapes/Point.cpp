#include "Point.h"

Point::Point(const double& ox, const double& oy)
{
	if (ox < 0 || oy < 0 || ox > 1000 || oy > 1000)
	{
		throw std::invalid_argument("x and y must be in range 0 - 1000");
	}

	m_x = ox;
	m_y = oy;
}

double Point::GetX() const
{
	return m_x;
}

double Point::GetY() const
{
	return m_y;
}