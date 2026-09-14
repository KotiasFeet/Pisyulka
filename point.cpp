#include "point.h"

void PointShape::Show(HDC hdc)
{
    int radius = 5;

    RGBColor fc = GetFillingColor();

	// If the color is -1, it means transparent, so we use NULL_BRUSH  
    HBRUSH hBrush = (fc.r != -1)
        ? CreateSolidBrush(RGB(fc.r, fc.g, fc.b))
        : (HBRUSH)GetStockObject(NULL_BRUSH);

    HPEN hPen = (HPEN)GetStockObject(NULL_PEN);

    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    Ellipse(hdc, x1_ - radius, y1_ - radius, x1_ + radius, y1_ + radius);

    SelectObject(hdc, hOldBrush);
    SelectObject(hdc, hOldPen);

    if (fc.r != -1) DeleteObject(hBrush);
}