#pragma once
#include "SolidShape.h"

class Triangle : public SolidShape
{
public:
	Triangle(const Point& point1, const Point& point2, const Point& point3, const uint32_t& outlineColor, const uint32_t& fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;
	void Draw(ICanvas& canvas) const override;

private:
	bool IsValidPoints(const Point& point1, const Point& point2, const Point& point3) const;
	Point m_vertex1 = { 0, 0 };
	Point m_vertex2 = { 0, 0 };
	Point m_vertex3 = { 0, 0 };
};