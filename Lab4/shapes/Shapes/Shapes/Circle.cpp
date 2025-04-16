#include "Circle.h"
#include <cmath>

Circle::Circle(const Point& center, const double& radius, const uint32_t& outlineColor, const uint32_t& fillColor)
{
	if (radius <= 0)
	{
		throw std::invalid_argument("Radius must be more than 0");
	}

	if ((center.GetX() - radius) <= 0 || (center.GetY() - radius) <= 0)
	{
		throw std::invalid_argument("Ñircle must be within the positive coordinate axes.");
	}

	if (outlineColor > 0xffffff || fillColor > 0xffffff)
	{
		throw std::invalid_argument("Ñolors must be in range #000000-#ffffff\n");
	}

	m_center = center;
	m_radius = radius;
	m_outlineColor = outlineColor;
	m_fillColor = fillColor;
}

double Circle::GetArea() const
{
	return std::acos(-1.0) * std::pow(m_radius, 2);
}

double Circle::GetPerimeter() const
{
	return 2 * std::acos(-1.0) * m_radius;
}
std::string Circle::ToString() const
{
	return "";
}

Point Circle::GetCenter() const
{
	return m_center;
}

double Circle::GetRadius() const
{
	return m_radius;
}

void Circle::Draw(ICanvas& canvas) const
{
	canvas.DrawCircle(m_center, m_radius, m_outlineColor);
	canvas.FillCircle(m_center, m_radius, m_fillColor);
}