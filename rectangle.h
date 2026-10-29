#pragma once

#include "shape.h"

class RectangleShape : public virtual Shape
{
public:
	RectangleShape(long x1, long y1, long x2, long y2) { Set(x1, y1, x2, y2); };
	virtual void Show(HDC hdc) override;
};