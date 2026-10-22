#include "OOLine.h"

void OOLineShape::Show(HDC hdc) {
    long x1 = LineShape::GetX1();
    long y1 = LineShape::GetY1();
    long x2 = LineShape::GetX2();
    long y2 = LineShape::GetY2();

    LineShape::Show(hdc);

    const int r = OOLINE_CIRCLE_RADIUS;

    EllipseShape::Set(x1 - r, y1 - r, x1 + r, y1 + r);
    EllipseShape::Show(hdc);

    EllipseShape::Set(x2 - r, y2 - r, x2 + r, y2 + r);
    EllipseShape::Show(hdc);

    LineShape::Set(x1, y1, x2, y2);
}