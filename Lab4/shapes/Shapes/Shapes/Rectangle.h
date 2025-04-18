#pragma once
#include "ICanvasDrawable.h"
#include "ISolidShape.h"

class Rectangle : public ISolidShape
	, public ICanvasDrawable
{
public:
	Rectangle(const Point& leftBottomPoint, const Point& rightTopPoint, const uint32_t& outlineColor, const uint32_t& fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	Point GetLeftTop() const;
	Point GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
	void Draw(ICanvas& canvas) const override;
	uint32_t GetFillColor() const override;
	uint32_t GetOutlineColor() const override;

private:
	double GetDistanceBetween(const Point& point1, const Point& point2) const;
	uint32_t m_outlineColor;
	uint32_t m_fillColor;
	Point m_leftTopPoint = { 0, 0 };
	Point m_rightBottomPoint = { 0, 0 };
};
