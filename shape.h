#pragma once

#include <windows.h>
#include "RGBColor.h"


/// <summary>
/// long x1, y1, x2, y2 - coordinates of the shape
/// RGBColor fillingColor_ - color of the shape filling
/// RGBColor outlineColor_ - color of the shape outline
/// </summary>
class Shape
{
protected:
	long x1_, y1_, x2_, y2_;

	RGBColor fillingColor_ = Palette::Black;
	RGBColor outlineColor_ = Palette::Black;
public:
	Shape();
	virtual ~Shape() {}

	void Set(long x1, long y1, long x2, long y2);
	virtual void Show(HDC hdc) = 0;

	void SetFillingColor(RGBColor c) { fillingColor_ = c; }
	RGBColor GetFillingColor() const { return fillingColor_; }

	void SetOutlineColor(RGBColor c) { outlineColor_ = c; }
	RGBColor GetOutlineColor() const { return outlineColor_; }

};