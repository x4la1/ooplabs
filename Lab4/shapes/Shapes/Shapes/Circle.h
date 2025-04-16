#pragma once
#include "SolidShape.h"

class Circle : public SolidShape
{
public:
	Circle(const Point& center, const double& radius, const uint32_t& outlineColor, const uint32_t& fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	Point GetCenter() const;
	double GetRadius() const;
	void Draw(ICanvas& canvas) const override;

private:
	Point m_center = { 0, 0 };
	double m_radius;
};