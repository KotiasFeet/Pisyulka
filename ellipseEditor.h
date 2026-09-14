#pragma once

#include "shapeEditor.h"
#include "ellipse.h"
#include "color.h"

class EllipseEditor : public ShapeEditor
{
protected:
	Shape* CreateShape(long x1, long y1, long x2, long y2) override;
public:
	EllipseEditor();
};
