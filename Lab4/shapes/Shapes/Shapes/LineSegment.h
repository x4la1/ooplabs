#pragma once
#include "Shape.h"

class LineSegment : public Shape
{
public:
	LineSegment(const Point& startPoint, const Point& endPoint, const uint32_t& outlineColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	Point GetStartPoint() const;
	Point GetEndPoint() const;
	void Draw(ICanvas& canvas) const override;

private:
	Point m_startPoint{ 0, 0 };
	Point m_endPoint{ 0, 0 };
};