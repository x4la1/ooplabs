#include "LineSegment.h"
#include <cmath>

LineSegment::LineSegment(const Point& startPoint, const Point& endPoint, const uint32_t& outlineColor)
{
	if (startPoint.GetX() == endPoint.GetX() && startPoint.GetY() == endPoint.GetY())
	{
		throw std::invalid_argument("Points must be different\n");
	}

	if (outlineColor > 0xffffff)
	{
		throw std::invalid_argument("Ñolors must be in range #000000-#ffffff\n");
	}

	m_startPoint = Point(startPoint.GetX(), m_windowsHeight - startPoint.GetY());
	m_endPoint = Point(endPoint.GetX(), m_windowsHeight - endPoint.GetY());
	m_outlineColor = outlineColor;
}

double LineSegment::GetArea() const
{
	return 0;
}

double LineSegment::GetPerimeter() const
{
	return std::sqrt(std::pow((m_endPoint.GetX() - m_startPoint.GetX()), 2) + std::pow((m_endPoint.GetY() - m_startPoint.GetY()), 2));
}

std::string LineSegment::ToString() const
{
	return "LineSegment";
}
Point LineSegment::GetStartPoint() const
{
	return m_startPoint;
}
Point LineSegment::GetEndPoint() const
{
	return m_endPoint;
}

void LineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}
