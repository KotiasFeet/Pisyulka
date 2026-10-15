#include "OOLine.h"

void OOLineShape::Show(HDC hdc) {

    LineShape::Show(hdc);

    long x1 = LineShape::GetX1();
    long y1 = LineShape::GetY1();
    long x2 = LineShape::GetX2();
    long y2 = LineShape::GetY2();

    const int r = OOLINE_CIRCLE_RADIUS;

    EllipseShape cir1(x1 - r, y1 - r, x1 + r, y1 + r);
    EllipseShape cir2(x2 - r, y2 - r, x2 + r, y2 + r);

    RGBColor oc = LineShape::GetOutlineColor();
    RGBColor fc = LineShape::GetFillingColor();

    cir1.SetFillingColor(fc);
    cir2.SetFillingColor(fc);
    cir1.SetOutlineColor(oc);
    cir2.SetOutlineColor(oc);

    cir1.Show(hdc);
    cir2.Show(hdc);
}