#pragma once
#include "Point.h"
#include <vector>

class ICanvas
{
public:
	virtual void DrawLine(const Point& from, const Point& to, const uint32_t& lineColor) const = 0;
	virtual void FillPolygon(const std::vector<Point>& points, const uint32_t& fillColor) const = 0;
	virtual void DrawCircle(const Point& center, const double& radius, const uint32_t& lineColor) const = 0;
	virtual void FillCircle(const Point& center, const double& radius, const uint32_t& fillColor) const = 0;
};