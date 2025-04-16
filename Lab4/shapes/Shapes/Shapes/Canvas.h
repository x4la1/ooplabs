#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class Canvas : public ICanvas
{
public:
	Canvas(sf::RenderWindow& window);
	void DrawLine(const Point& from, const Point& to, const uint32_t& lineColor) const override;
	void FillPolygon(const std::vector<Point>& points, const uint32_t& fillColor) const override;
	void DrawCircle(const Point& center, const double& radius, const uint32_t& lineColor) const override;
	void FillCircle(const Point& center, const double& radius, const uint32_t& fillColor) const override;

private:
	sf::RenderWindow& m_window;
	sf::Color ConvertToRgba(const uint32_t& color) const;
};