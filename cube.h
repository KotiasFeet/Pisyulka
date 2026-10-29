#pragma once

#include "rectangle.h"
#include "line.h"

class CubeShape : public RectangleShape, public LineShape
{
public:
	CubeShape(long x1, long y1, long x2, long y2) 
		: Shape()
		, RectangleShape(x1, y1, x2, y2)
		, LineShape(x1, y1, x2, y2) {}

	virtual void Show(HDC hdc) override;
};