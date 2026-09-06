#include "point.h"

void PointShape::Show(HDC hdc)
{
	SetPixel(hdc, x1_, y1_, RGB(0, 0, 0));
}

//void PointShape::Show(HDC hdc)
//{
//    const int r = 2; // radius of visible point
//    Ellipse(hdc, x1_ - r, y1_ - r, x1_ + r, y1_ + r);
//}