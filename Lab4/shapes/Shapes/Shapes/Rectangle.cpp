#include "Rectangle.h"
#include <cmath>

Rectangle::Rectangle(const Point& leftTopPoint, const Point& rightBottomPoint, const uint32_t& outlineColor, const uint32_t& fillColor)
{
	if (leftTopPoint.GetX() >= rightBottomPoint.GetX() || leftTopPoint.GetY() <= rightBottomPoint.GetY())
	{
		throw std::invalid_argument("Invalid rectangle\n");
	}

	if (outlineColor > 0xffffff || fillColor > 0xffffff || outlineColor < 0x000000 || fillColor < 0x000000)
	{
		throw std::invalid_argument("Colors must be in range #000000-#ffffff\n");
	}

	m_leftTopPoint = leftTopPoint;
	m_rightBottomPoint = rightBottomPoint; 
	m_outlineColor = outlineColor;
	m_fillColor = fillColor;
}

uint32_t Rectangle::GetFillColor() const
{
	return m_fillColor;
}
uint32_t Rectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

double Rectangle::GetDistanceBetween(const Point& point1, const Point& point2) const
{
	return (std::sqrt(std::pow((point2.GetY() - point1.GetY()), 2) + std::pow((point2.GetX() - point1.GetX()), 2)));
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
	return m_leftTopPoint;
}

Point Rectangle::GetRightBottom() const
{
	return m_rightBottomPoint;
}

double Rectangle::GetWidth() const
{
	return m_rightBottomPoint.GetX() - m_leftTopPoint.GetX();
}

double Rectangle::GetHeight() const
{
	return m_leftTopPoint.GetY() - m_rightBottomPoint.GetY();
}

void Rectangle::Draw(ICanvas& canvas) const
{
	Point point1 = m_leftTopPoint;
	Point point2(m_rightBottomPoint.GetX(), m_leftTopPoint.GetY());
	Point point3 = m_rightBottomPoint;
	Point point4(m_leftTopPoint.GetX(), m_rightBottomPoint.GetY());
	canvas.FillPolygon(std::vector<Point>{ point1, point2, point3, point4 }, m_fillColor);
	canvas.DrawLine(point1, point2, m_outlineColor);
	canvas.DrawLine(point2, point3, m_outlineColor);
	canvas.DrawLine(point3, point4, m_outlineColor);
	canvas.DrawLine(point4, point1, m_outlineColor);
}