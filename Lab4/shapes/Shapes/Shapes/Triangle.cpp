#include "Triangle.h"
#include <cmath>

Triangle::Triangle(const Point& point1, const Point& point2, const Point& point3, const uint32_t& outlineColor, const uint32_t& fillColor)
{
	if (!IsValidPoints(point1, point2, point3))
	{
		throw std::invalid_argument("Wrong triangle");
	}

	if (outlineColor > 0xffffff || fillColor > 0xffffff)
	{
		throw std::invalid_argument("Ñolors must be in range #000000-#ffffff\n");
	}

	m_vertex1 = point1;
	m_vertex2 = point2;
	m_vertex3 = point3;
	m_outlineColor = outlineColor;
	m_fillColor = fillColor;
}

double Triangle::GetArea() const
{
	return 0.5 * std::abs(m_vertex1.GetX() * (m_vertex2.GetY() - m_vertex3.GetY()) + m_vertex2.GetX() * (m_vertex3.GetY() - m_vertex1.GetY()) + m_vertex3.GetX() * (m_vertex1.GetY() - m_vertex2.GetY()));
}
double Triangle::GetPerimeter() const
{
	return GetDistanceBetween(m_vertex1, m_vertex2) + GetDistanceBetween(m_vertex2, m_vertex3) + GetDistanceBetween(m_vertex1, m_vertex3);
}

bool Triangle::IsValidPoints(const Point& point1, const Point& point2, const Point& point3) const
{
	if ((GetDistanceBetween(point1, point2) + GetDistanceBetween(point2, point3)) <= GetDistanceBetween(point1, point3) || (GetDistanceBetween(point2, point3) + GetDistanceBetween(point1, point3)) <= GetDistanceBetween(point1, point2) || (GetDistanceBetween(point1, point3) + GetDistanceBetween(point1, point2)) <= GetDistanceBetween(point2, point3))
	{
		return false;
	}

	return true;
}

Point Triangle::GetVertex1() const
{
	return m_vertex1;
}

Point Triangle::GetVertex2() const
{
	return m_vertex2;
}

Point Triangle::GetVertex3() const
{
	return m_vertex3;
}

std::string Triangle::ToString() const
{
	return "";
}

void Triangle::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_vertex1, m_vertex2, m_outlineColor);
	canvas.DrawLine(m_vertex2, m_vertex3, m_outlineColor);
	canvas.DrawLine(m_vertex3, m_vertex1, m_outlineColor);
	canvas.FillPolygon(std::vector<Point>{ m_vertex1, m_vertex2, m_vertex3 }, m_fillColor);
}