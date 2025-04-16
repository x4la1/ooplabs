#pragma once
#include <stdexcept>

class Point
{
public:
	Point(const double& ox, const double& oy);
	double GetX() const;
	double GetY() const;

private:
	double m_x;
	double m_y;
};