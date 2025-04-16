#include "Canvas.h"
#include <stdexcept>

Canvas::Canvas(sf::RenderWindow& window)
	: m_window{ window }
{
}

void Canvas::DrawLine(const Point& from, const Point& to, const uint32_t& lineColor) const
{
	sf::Color color = ConvertToRgba(lineColor);

	sf::Vertex vertices[2];
	vertices[0].position = sf::Vector2f(static_cast<float>(from.GetX()), static_cast<float>(from.GetY()));
	vertices[0].color = color;
	vertices[1].position = sf::Vector2f(static_cast<float>(to.GetX()), static_cast<float>(to.GetY()));
	vertices[1].color = color;

	m_window.draw(vertices, 2, sf::PrimitiveType::Lines);
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
		polygon.setPoint(i, sf::Vector2f(points[i].GetX(), points[i].GetY()));
	}

	m_window.draw(polygon);
}

void Canvas::DrawCircle(const Point& center, const double& radius, const uint32_t& lineColor) const
{
	sf::CircleShape circle(radius);
	circle.setPosition(sf::Vector2f(static_cast<float>(center.GetX() - radius), static_cast<float>(center.GetY() - radius)));
	circle.setOutlineColor(ConvertToRgba(lineColor));
	circle.setOutlineThickness(1);
	circle.setFillColor(sf::Color::Transparent);

	m_window.draw(circle);
}

void Canvas::FillCircle(const Point& center, const double& radius, const uint32_t& fillColor) const
{
	sf::CircleShape circle(radius);
	circle.setPosition(sf::Vector2f(static_cast<float>(center.GetX() - radius), static_cast<float>(center.GetY() - radius)));
	circle.setFillColor(ConvertToRgba(fillColor));
	circle.setOutlineThickness(0);

	m_window.draw(circle);
}

sf::Color Canvas::ConvertToRgba(const uint32_t& color) const
{
	return sf::Color((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF, (color >> 24) & 0xFF);
}