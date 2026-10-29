#pragma once

#include "shape.h"
#include "color.h"

class PointShape : public virtual Shape
{
public:
	PointShape(long x, long y) { Set(x, y, x, y); }
	virtual void Show(HDC hdc) override;

	long GetX1() const { return x1_+10; }
	long GetY1() const { return y1_+10; }
	long GetX2() const { return x2_-10; }
	long GetY2() const { return y2_-10; }
};