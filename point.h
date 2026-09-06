#pragma once

#include "shape.h"

class PointShape : public Shape
{
public:
	PointShape(long x, long y) { Set(x, y, x, y); }
	virtual void Show(HDC hdc) override;
};