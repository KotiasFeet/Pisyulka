#include "ellipse.h"

void EllipseShape::Show(HDC hdc)
{
    RGBColor oc = GetOutlineColor();
    RGBColor fc = GetFillingColor();

    bool hasOutline = (oc.r != -1);
    bool hasFill = (fc.r != -1);

    if (!hasOutline && !hasFill) return;


    HBRUSH hBrush = hasFill
        ? CreateSolidBrush(RGB(fc.r, fc.g, fc.b))
        : (HBRUSH)GetStockObject(NULL_BRUSH);

    HPEN hPen = hasOutline
        ? CreatePen(PS_SOLID, 1, RGB(oc.r, oc.g, oc.b))
        : (HPEN)GetStockObject(NULL_PEN);

    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    Ellipse(hdc, x1_, y1_, x2_, y2_);

    SelectObject(hdc, hOldBrush);
    SelectObject(hdc, hOldPen);

    if (hasFill) DeleteObject(hBrush);
    if (hasOutline) DeleteObject(hPen);
}