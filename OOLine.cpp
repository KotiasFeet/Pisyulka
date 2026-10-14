#include "OOLine.h"

void OOLineShape::Show(HDC hdc) {

	RGBColor oc = GetOutlineColor();
	RGBColor fc = GetFillingColor();

	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(oc.r, oc.g, oc.b));
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	
	MoveToEx(hdc, x1_, y1_, NULL);
	LineTo(hdc, x2_, y2_);

	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);

}