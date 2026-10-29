#pragma once

#include "line.h"
#include "ellipse.h"

class OOLineShape : public LineShape, EllipseShape
{
public:
	OOLineShape(long x1, long y1, long x2, long y2)
		: Shape()
		, LineShape(x1, y1, x2, y2)
		, EllipseShape(x1, y1, x2, y2) {}
	
	virtual void Show(HDC hdc) override;
};