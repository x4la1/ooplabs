#pragma once
#include "ICanvasDrawable.h"
#include "ISolidShape.h"

class Circle : public ISolidShape
	, public ICanvasDrawable
{
public:
	Circle(const Point& center, const double& radius, const uint32_t& outlineColor, const uint32_t& fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	Point GetCenter() const;
	double GetRadius() const;
	uint32_t GetOutlineColor() const override;
	uint32_t GetFillColor() const override;
	void Draw(ICanvas& canvas) const override;

private:
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
	Point m_center = { 0, 0 };
	double m_radius;
};