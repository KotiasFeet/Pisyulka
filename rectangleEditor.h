#pragma once

#include "shapeEditor.h"
#include "rectangle.h"
#include "color.h"

class RectangleEditor : public ShapeEditor
{
protected:
	Shape* CreateShape(long x1, long y1, long x2, long y2) override;
public:
	RectangleEditor();
};