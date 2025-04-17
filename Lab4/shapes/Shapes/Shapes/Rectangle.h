#pragma once
#include "SolidShape.h"


class Rectangle : public SolidShape
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

public:
	Point m_leftBottomPoint = { 0, 0 };
	Point m_rightTopPoint = { 0, 0 };
};
