#include "cube.h"

void CubeShape::Show(HDC hdc) {
    long x1 = RectangleShape::GetX1();
    long y1 = RectangleShape::GetY1();
    long x2 = RectangleShape::GetX2();
    long y2 = RectangleShape::GetY2();

    int offset = (x2 - x1) / 3;


    RectangleShape::Set(x1 + offset, y1 - offset, x2 + offset, y2 - offset);
    RectangleShape::Show(hdc);

    LineShape::Set(x1, y1, x1 + offset, y1 - offset);
    LineShape::Show(hdc);

    LineShape::Set(x2, y1, x2 + offset, y1 - offset);
    LineShape::Show(hdc);

    LineShape::Set(x1, y2, x1 + offset, y2 - offset);
    LineShape::Show(hdc);

    LineShape::Set(x2, y2, x2 + offset, y2 - offset);
    LineShape::Show(hdc);

    RectangleShape::Set(x1, y1, x2, y2);
    RectangleShape::Show(hdc);
}