#include "Rectangle.h"

Rectangle::Rectangle(const Point& leftBottomPoint, const Point& rightTopPoint, const uint32_t& outlineColor, const uint32_t& fillColor)
{
	if (leftBottomPoint.GetX() >= rightTopPoint.GetX() || leftBottomPoint.GetY() >= rightTopPoint.GetY())
	{
		throw std::exception("Invalid rectangle\n");
	}

	if (outlineColor > 0xffffff || fillColor > 0xffffff)
	{
		throw std::invalid_argument("Ñolors must be in range #000000-#ffffff\n");
	}

	m_leftBottomPoint = Point(leftBottomPoint.GetX(), m_windowsHeight - leftBottomPoint.GetY());
	m_rightTopPoint = Point(rightTopPoint.GetX(), m_windowsHeight - rightTopPoint.GetY());
	m_outlineColor = outlineColor;
	m_fillColor = fillColor;
}

double Rectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

double Rectangle::GetPerimeter() const
{
	return (GetWidth() + GetHeight()) * 2;
}

std::string Rectangle::ToString() const
{
	return "Rectangle";
}

Point Rectangle::GetLeftTop() const
{
	return m_leftBottomPoint;
}

Point Rectangle::GetRightBottom() const
{
	return m_rightTopPoint;
}

double Rectangle::GetWidth() const
{
	return m_rightTopPoint.GetX() - m_leftBottomPoint.GetX();
}

double Rectangle::GetHeight() const
{
	return m_leftBottomPoint.GetY() - m_rightTopPoint.GetY();
}

void Rectangle::Draw(ICanvas& canvas) const
{
	Point point1 = m_leftBottomPoint;
	Point point2(m_rightTopPoint.GetX(), m_leftBottomPoint.GetY());
	Point point3 = m_rightTopPoint;
	Point point4(m_leftBottomPoint.GetX(), m_rightTopPoint.GetY());
	canvas.FillPolygon(std::vector<Point>{ point1, point2, point3, point4 }, m_fillColor);
	canvas.DrawLine(point1, point2, m_outlineColor);
	canvas.DrawLine(point2, point3, m_outlineColor);
	canvas.DrawLine(point3, point4, m_outlineColor);
	canvas.DrawLine(point4, point1, m_outlineColor);
}