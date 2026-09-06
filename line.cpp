#include "line.h"

void LineShape::Show(HDC hdc)
{
	MoveToEx(hdc, x1_, y1_, NULL);
	LineTo(hdc, x2_, y2_);
}