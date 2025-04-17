#include "Canvas.h"
#include <stdexcept>

Canvas::Canvas(sf::RenderWindow& window)
	: m_window{ window }
{
}

void Canvas::DrawLine(const Point& from, const Point& to, const uint32_t& lineColor) const
{
	sf::Vector2f dir(to.GetX() - from.GetX(), to.GetY() - from.GetY());
	sf::Vector2f perpendicular(-dir.y, dir.x);
	float length = std::sqrt(perpendicular.x * perpendicular.x + perpendicular.y * perpendicular.y);
	perpendicular /= length;
	perpendicular *= 1.5f;

	sf::ConvexShape thickLine;
	thickLine.setPointCount(4);
	thickLine.setPoint(0, sf::Vector2f(from.GetX() + perpendicular.x, from.GetY() + perpendicular.y));
	thickLine.setPoint(1, sf::Vector2f(from.GetX() - perpendicular.x, from.GetY() - perpendicular.y));
	thickLine.setPoint(2, sf::Vector2f(to.GetX() - perpendicular.x, to.GetY() - perpendicular.y));
	thickLine.setPoint(3, sf::Vector2f(to.GetX() + perpendicular.x, to.GetY() + perpendicular.y));
	thickLine.setFillColor(ConvertToRgba(lineColor));

	m_window.draw(thickLine);
}

void Canvas::FillPolygon(const std::vector<Point>& points, const uint32_t& fillColor) const
{
	if (points.size() < 3)
	{
		throw std::runtime_error("Count of points must be more than 2");
	}

	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	polygon.setFillColor(ConvertToRgba(fillColor));

	for (size_t i = 0; i < points.size(); ++i)
	{
		polygon.setPoint(i, sf::Vector2f(static_cast<float>(points[i].GetX()), static_cast<float>(points[i].GetY())));
	}
	m_window.draw(polygon);
}

void Canvas::DrawCircle(const Point& center, const double& radius, const uint32_t& lineColor) const
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setPosition(
		static_cast<float>(center.GetX() - radius),
		static_cast<float>(center.GetY() - radius));
	circle.setOutlineColor(ConvertToRgba(lineColor));
	circle.setOutlineThickness(3.0f);
	circle.setFillColor(sf::Color::Transparent);
	m_window.draw(circle);
}

void Canvas::FillCircle(const Point& center, const double& radius, const uint32_t& fillColor) const
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setPosition(
		static_cast<float>(center.GetX() - radius),
		static_cast<float>(center.GetY() - radius));
	circle.setFillColor(ConvertToRgba(fillColor));
	circle.setOutlineThickness(0);
	m_window.draw(circle);
}

sf::Color Canvas::ConvertToRgba(const uint32_t& color) const
{
	return sf::Color(
		(color >> 16) & 0xFF,
		(color >> 8) & 0xFF,
		color & 0xFF,
		255);
}