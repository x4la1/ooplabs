#pragma once
#include "IShape.h"
#include "ICanvasDrawable.h"

class LineSegment : public IShape, public ICanvasDrawable
{
public:
	LineSegment(const Point& startPoint, const Point& endPoint, const uint32_t& outlineColor);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	Point GetStartPoint() const;
	Point GetEndPoint() const;
	void Draw(ICanvas& canvas) const override;
	uint32_t GetOutlineColor() const override;

private:
	uint32_t m_outlineColor;
	Point m_startPoint{ 0, 0 };
	Point m_endPoint{ 0, 0 };
};