#include "cube.h"

void CubeShape::Show(HDC hdc) {

	long x1 = RectangleShape::GetX1();
	long y1 = RectangleShape::GetY1();
	long x2 = RectangleShape::GetX2();
	long y2 = RectangleShape::GetY2();

	int offset = (x2 - x1) / 3;

	RectangleShape frontRect(x1, y1, x2, y2);
	RectangleShape backRect(x1 + offset, y1 - offset, x2 + offset, y2 - offset);
	
	RGBColor oc = RectangleShape::GetOutlineColor();
	RGBColor fc = RectangleShape::GetFillingColor();

	frontRect.SetOutlineColor(oc);
	frontRect.SetFillingColor(fc);
	backRect.SetOutlineColor(oc);
	backRect.SetFillingColor(fc);

	backRect.Show(hdc);
	frontRect.Show(hdc);

	// Top-left
	{
		LineShape l(x1, y1, x1 + offset, y1 - offset);
		l.SetOutlineColor(oc);
		l.Show(hdc);
	}
	// Top-right
	{
		LineShape l(x2, y1, x2 + offset, y1 - offset);
		l.SetOutlineColor(oc);
		l.Show(hdc);
	}
	// Bottom-left
	{
		LineShape l(x1, y2, x1 + offset, y2 - offset);
		l.SetOutlineColor(oc);
		l.Show(hdc);
	}
	// Bottom-right
	{
		LineShape l(x2, y2, x2 + offset, y2 - offset);
		l.SetOutlineColor(oc);
		l.Show(hdc);
	}

}