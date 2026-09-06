#pragma once

#include "shape.h"

class LineShape : public Shape
{
public:
	LineShape(long x1, long y1, long x2, long y2) { Set(x1, y1, x2, y2); }
	virtual void Show(HDC hdc) override;

	// Public accessors
	long GetX1() const { return x1_; }
	long GetY1() const { return y1_; }
	long GetX2() const { return x2_; }
	long GetY2() const { return y2_; }
};