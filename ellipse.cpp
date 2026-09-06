#include "ellipse.h"

void EllipseShape::Show(HDC hdc)
{
	Ellipse(hdc, x1_, y1_, x2_, y2_);
}